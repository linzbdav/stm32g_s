//---------------------------------------------------------------------------
// Titel        : Stepper Driver STM32F0
//---------------------------------------------------------------------------
// Funktion     : Stepper Funktionen
// Schaltung    :
//---------------------------------------------------------------------------
// Hardware     : STM32F051
// Takt         : 48MHz
// Sprache      : ARM C
// Datum        : 14.11.2014
// Version      : 1
// Autor        : David Linzberger
//---------------------------------------------------------------------------
#include "main.h"
#include "segment.h"
#include "stepper.h"
#include "encoder.h"

#include "DRV8711/DRV8711_registers.h"
#include "DRV8711/DRV8711_utility.h"

/* Allocate structures */
stPrepSingleton_t st_prep;
stConfig_t st_cfg;
static stRunSingleton_t st_run;

/* Setup local functions */
static void _load_move();
static void _request_load_move();
static stat_t _prep_line( seg_def_t *seg );
static void _energize_motor( const uint8_t m );
static void _deenergize_motor( const uint8_t m );
static void _init_register();
static void _reset_motor( uint8_t m );
static void _set_hw_torque( const uint8_t motor, const uint8_t torque );
static void _set_hw_microsteps( const uint8_t motor, const uint16_t microsteps );
static void _motor_step( const uint8_t motor );

// handy macro
#define _f_to_periode(f) (uint16_t)((rcc_core_frequency / f) - 1 )

void stepper_init()
{
	memset(&st_run, 0, sizeof(st_run));
	stepper_init_assertions();
	
    rcc_periph_clock_enable( RCC_TIM1 );
	rcc_periph_clock_enable( RCC_TIM2 );
	rcc_periph_clock_enable( RCC_TIM3 );
	
	nvic_enable_irq( NVIC_TIM1_CC_IRQ );
	//nvic_set_priority( 0 );
	nvic_enable_irq( NVIC_TIM2_IRQ );
	//nvic_set_priority( 1 );
	nvic_enable_irq( NVIC_TIM3_IRQ );
	//nvic_set_priority( 1 );
	
	timer_set_mode( TIM1, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP );
	timer_set_period( TIM1, ( 48000000 / 50000 ) - 1 );
	timer_set_prescaler( TIM1, 0 );
	
	timer_set_mode( TIM2, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP );
	timer_set_period( TIM2, ( 48000000 / 50000 ) - 1 );
	timer_set_prescaler( TIM2, 0 );
	
	timer_set_mode( TIM3, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP );
	timer_set_period( TIM3, ( 48000000 / 50000 ) - 1 );
	timer_set_prescaler( TIM3, 0 );
	
	timer_disable_oc_clear( TIM1, TIM_OC1 );
	timer_disable_oc_preload( TIM1, TIM_OC1 );
	timer_set_oc_slow_mode( TIM1, TIM_OC1 );
	timer_set_oc_mode( TIM1, TIM_OC1, TIM_OCM_FROZEN );
	
	timer_set_oc_value( TIM1, TIM_OC1, 100 );
	
	timer_enable_irq( TIM3, TIM_DIER_UIE );
	timer_enable_irq( TIM2, TIM_DIER_UIE );
	timer_enable_irq( TIM1, TIM_DIER_CC1IE | TIM_DIER_UIE );
	
    // Map motor
    st_cfg.m[0].map = &hw.st[0];
    st_cfg.m[1].map = &hw.st[1];
    st_cfg.m[2].map = &hw.st[2];

    DRV8711_init( st_cfg.m[0].map );
    DRV8711_init( st_cfg.m[1].map );
    DRV8711_init( st_cfg.m[2].map );

	st_prep.exec_state = PREP_BUFFER_OWNED_BY_EXEC;
}

void stepper_init_assertions()
{
	st_run.magic_end = MAGICNUM;
	st_run.magic_start = MAGICNUM;
	st_prep.magic_end = MAGICNUM;
	st_prep.magic_start = MAGICNUM;
}

stat_t stepper_test_assertions()
{
	if( st_run.magic_end	!= MAGICNUM ) return (STAT_STEPPER_ASSERTION_FAILURE );
	if( st_run.magic_start	!= MAGICNUM ) return (STAT_STEPPER_ASSERTION_FAILURE );
	if( st_prep.magic_end	!= MAGICNUM ) return (STAT_STEPPER_ASSERTION_FAILURE );
	if( st_prep.magic_start	!= MAGICNUM ) return (STAT_STEPPER_ASSERTION_FAILURE );
	return( STAT_OK );
}

/*
 * st_runtime_isbusy() - return TRUE if runtime is busy:
 * 
 * 		Busy conditions:
 * 		 - motor are running
 * 		 - dwell is running
 */
uint8_t st_runtime_isbusy()
{
	if( st_run.dda_ticks_downcount == 0 )
	{
		return false;
	}
	return true;
}

/*
 * st_reset() - reset stepper internals
 */
void st_reset_motors( )
{
	uint8_t i;
	
	for( i = 0; i < MOTORn; i++ )
	{ 
		_reset_motor(i);
		st_prep.m[i].prev_direction = 0;
		st_run.m[i].substep_accumulator = 0;
		st_prep.m[i].corrected_steps = 0;
    }
    
    _init_register();
}



uint16_t st_get_status()
{
	uint8_t dataHi, dataLo = 0;
	dataHi = REGREAD | (st_cfg.m[0].map->drv.CTRL.Address << 4);
    return SPI_DRV8711_ReadWrite( st_cfg.m[0].map, dataHi, dataLo);
}

static void _init_register()
{
    uint8_t i;

    // Read Register
    for( i = 0; i < 3; i++ )
    {
        // Load default value from device
        G_READ_ALL_REG = true;
        UpdateDRV8711Registers( st_cfg.m[i].map );
        // Set default value
        st_cfg.m[i].microsteps = st_cfg.m[i].map->drv.CTRL.MODE;
    }
}

static void _reset_motor( uint8_t m )
{
    if( m > 2 )
        return;

    DRV8711_init( st_cfg.m[m].map );
}

void st_set_motor_torque( uint8_t motor, uint8_t torque )
{
    if( motor > 2 )
        return;

    _set_hw_torque( motor, torque );
}

void st_set_motor_microstep( uint8_t motor, uint16_t microstep )
{
    if( motor > 2 )
        return;

    _set_hw_microsteps( motor, microstep );
}

void st_enable_motor( uint8_t motor )
{
    if( motor < 3 )
        _energize_motor( motor );
}

void st_disable_motor( uint8_t motor )
{
    if( motor < 3 )
        _deenergize_motor( motor );
}

void st_step_motor( uint8_t motor )
{
    if( motor < 3 )
        _motor_step( motor );
}

uint8_t st_isbusy()
{
    if( st_run.dda_ticks_downcount == 0 )
    {
        return false;
    }
    return true;
}

static void _energize_motor( const uint8_t m )
{
	struct CTRL_Register *G_CTRL_REG;

	pin_set( &st_cfg.m[m].map->sleep );

	G_CTRL_REG = &st_cfg.m[m].map->drv.CTRL;
	G_CTRL_REG->ENBL = 1;

    G_MANUAL_WRITE = true;
    G_WRITE_ADDR = G_CTRL_REG->Address;
    G_WRITE_DATA = (G_CTRL_REG->DTIME << 10) | (G_CTRL_REG->ISGAIN << 8)
				 | (G_CTRL_REG->EXSTALL << 7) | (G_CTRL_REG->MODE << 3)
				 | (G_CTRL_REG->RSTEP << 2) | (G_CTRL_REG->RDIR << 1) 
				 | (G_CTRL_REG->ENBL);
    UpdateDRV8711Registers( st_cfg.m[m].map );
}

static void _deenergize_motor( const uint8_t m )
{
    if( m > 2 )
        return;

	struct CTRL_Register *G_CTRL_REG;

    //if( !st.m[m].map->drv.ctrl.enbl )
    //    return;

	pin_reset( &st_cfg.m[m].map->sleep );

	G_CTRL_REG = &st_cfg.m[m].map->drv.CTRL;
	G_CTRL_REG->ENBL = 0;

	G_MANUAL_WRITE = true;
    G_WRITE_ADDR = G_CTRL_REG->Address;
    G_WRITE_DATA = (G_CTRL_REG->DTIME << 10) | (G_CTRL_REG->ISGAIN << 8)
				 | (G_CTRL_REG->EXSTALL << 7) | (G_CTRL_REG->MODE << 3)
				 | (G_CTRL_REG->RSTEP << 2) | (G_CTRL_REG->RDIR << 1)
				 | (G_CTRL_REG->ENBL);
    UpdateDRV8711Registers( st_cfg.m[m].map );
}


void st_energize_motors()
{
    uint8_t i;
    for( i = 0; i < 3; i++ )
    {
        _energize_motor( i );
    }
}

void st_deenergize_motors()
{
    uint8_t i;
    for( i = 0; i < 3; i++ )
    {
        _deenergize_motor( i );
    }
}

void st_request_prep_move()
{
	if( st_prep.exec_state == PREP_BUFFER_OWNED_BY_EXEC )
	{
		timer_set_counter( TIM2, 0 );
		timer_enable_counter( TIM2 );
	}
}

void TIM2_IRQHandler(void)
{
	timer_disable_counter( TIM2 );
	seg_def_t *s;
	timer_clear_flag( TIM2, TIM_SR_UIF );
	if( st_prep.exec_state == PREP_BUFFER_OWNED_BY_EXEC )
	{
		s = se_get_run_buffer();

		if( _prep_line( s ) == STAT_OK )
		{
			st_prep.exec_state = PREP_BUFFER_OWNED_BY_LOADER;
			_request_load_move();
		}
	}
}

void _request_load_move()
{
	if( st_run.dda_ticks_downcount == 0 )
	{
	    st_energize_motors();
		timer_set_counter( TIM3, 0 );
		timer_enable_counter( TIM3 );
	}
}

void TIM3_IRQHandler(void)
{
	timer_disable_counter( TIM3 );
	timer_clear_flag( TIM3, TIM_SR_UIF );
	_load_move();
}

void TIM1_IRQHandler(void)
{
	uint8_t i;
	if( timer_get_flag( TIM1, TIM_SR_UIF ) != 0 )
	{
		timer_clear_flag( TIM1, TIM_SR_UIF );
		for( i = 0; i < 3; i++ )
		{
			if( ( st_run.m[i].substep_accumulator += st_run.m[i].substep_increment ) > 0 )
			{
				pin_set( &hw.st[i].step );
				st_run.m[i].substep_accumulator -= st_run.dda_ticks_X_substeps;
				INCREMENT_ENCODER(i);
			}

			st_run.dda_ticks_downcount--;
			_request_load_move();
		}
	}
	else if( timer_get_flag( TIM1, TIM_SR_CC1IF ) != 0 )
	{
		timer_clear_flag( TIM1, TIM_SR_CC1IF );
		for( i = 0; i < 3; i++ )
		{
			pin_reset( &hw.st[i].step );
		}

		if( st_run.dda_ticks_downcount != 0 ) return;
		timer_disable_counter( TIM1 );
	}
}


static void _load_move()
{
	uint8_t i;
	
	if( st_runtime_isbusy() )
		return;

	if( st_prep.exec_state != PREP_BUFFER_OWNED_BY_LOADER )
	{	// no moves to load ...
		// shutdown the motors
		st_deenergize_motors();
		return;
	}

	if( st_prep.move_type == MOVE_TYPE_ALINE )
	{
		st_run.dda_ticks_downcount  = st_prep.dda_ticks;
		st_run.dda_ticks_X_substeps = st_prep.dda_ticks_X_substeps;

		for( i = 0; i < 3; i++ )
		{
			if( ( st_run.m[i].substep_increment = st_prep.m[i].substep_increment ) != 0 )
			{
				if( st_prep.m[i].accumulator_correction_flag == true )
				{
					st_prep.m[i].accumulator_correction_flag = false;
					st_run.m[i].substep_accumulator *= st_prep.m[i].accumulator_correction;
				}

				if( st_prep.m[i].direction != st_prep.m[i].prev_direction )
				{
					st_prep.m[i].prev_direction = st_prep.m[i].direction;
					st_run.m[i].substep_accumulator = -(st_run.dda_ticks_X_substeps + st_run.m[i].substep_accumulator );
					if( st_prep.m[i].direction == 1 )
					{
						pin_set( &hw.st[i].dir );
					}
					else
					{
						pin_reset( &hw.st[i].dir );
					}
				}

				// Enable Motor
				st_run.m[i].power_state = MOTOR_RUNNING;
				SET_ENCODER_STEP_SIGN( i, st_prep.m[i].step_sign );
			}
			else
			{

			}
			ACCUMULATE_ENCODER( i );
		}
		timer_enable_counter( TIM1 );
	}
	else if( st_prep.move_type == MOVE_TYPE_DWELL )
	{
		st_run.dda_ticks_downcount = st_prep.dda_ticks;
		timer_enable_counter( TIM1 );
	}

	st_prep_null();
	st_prep.exec_state = PREP_BUFFER_OWNED_BY_EXEC;
	st_request_prep_move();
}

void st_prep_null()
{
	st_prep.move_type = MOVE_TYPE_NULL;
}

stat_t _prep_line( seg_def_t *seg )
{
	uint8_t i;
	/*
	if( seg == NULL ) return STAT_EAGAIN;

	if( st_prep.exec_state != PREP_BUFFER_OWNED_BY_EXEC )
	{
		return STAT_INTERNAL_ERROR;
	}

	st_prep.dda_ticks_X_substeps = (uint32_t)( iq_muli( seg->time, FREQUENCY_DDA / 1000 ) );
	st_prep.dda_ticks = st_prep.dda_ticks_X_substeps >> 14;


	for( i = 0; i < 3; i++ )
	{
		st_prep.m[i].accumulator_correction_flag = false;

		if( seg->position[i] == 0 )
		{
			st_prep.m[i].substep_increment = 0;
			continue;
		}

		if( seg->direction[i] == 1 )
		{
			st_prep.m[i].direction = 1;// ^ st_cfg.m[i].polarity;
			st_prep.m[i].step_sign = 1;
		}
		else
		{
			st_prep.m[i].direction = 0;// ^ st_cfg.m[i].polarity;
			st_prep.m[i].step_sign = -1;
		}

		if( iq_sub( seg->time, st_prep.m[i].prev_segment_time ) > 0 )
		{
			if( st_prep.m[i].prev_segment_time != 0 )
			{
				st_prep.m[i].accumulator_correction_flag = true;
				st_prep.m[i].accumulator_correction = iq_div( seg->time, st_prep.m[i].prev_segment_time );
			}
			st_prep.m[i].prev_segment_time = seg->time;
		}

		st_prep.m[i].substep_increment = iq_mul( seg->position[i], st.m[i].steps_per_unit );
	}

	st_prep.move_type = seg->move_type;
	*/
	return STAT_OK;
}

static void _set_hw_microsteps( const uint8_t motor, const uint16_t microsteps )
{
	struct CTRL_Register *G_CTRL_REG;

    if( microsteps > 256 || motor > 2 )
        return;
    if( st_cfg.m[motor].microsteps == microsteps )
        return;
   
	G_CTRL_REG = &st_cfg.m[motor].map->drv.CTRL;
	G_CTRL_REG->MODE = microsteps;
	
	G_MANUAL_WRITE = true;
	G_WRITE_ADDR = G_CTRL_REG->Address;
	G_WRITE_DATA = (G_CTRL_REG->DTIME << 10) | (G_CTRL_REG->ISGAIN << 8)
				 | (G_CTRL_REG->EXSTALL << 7) | (G_CTRL_REG->MODE << 3)
				 | (G_CTRL_REG->RSTEP << 2) | (G_CTRL_REG->RDIR << 1)
				 | (G_CTRL_REG->ENBL);
	UpdateDRV8711Registers( st_cfg.m[motor].map );
	
	st_cfg.m[motor].microsteps = microsteps;
}

static void _set_hw_torque( const uint8_t motor, const uint8_t torque )
{
	struct TORQUE_Register *G_TORQUE_REG;
	
	G_TORQUE_REG = &st_cfg.m[motor].map->drv.TORQUE;
	
	if( motor > 2 )
		return;
	if( G_TORQUE_REG->TORQUE == torque )
		return;
	
    G_TORQUE_REG->TORQUE = torque;
    G_MANUAL_WRITE = true;
    G_WRITE_ADDR = G_TORQUE_REG->Address;
    G_WRITE_DATA = ( G_TORQUE_REG->SIMPLTH << 8 ) | (G_TORQUE_REG->TORQUE);
    UpdateDRV8711Registers( st_cfg.m[motor].map );
}

static void _motor_step( const uint8_t motor )
{
	uint16_t i = 0;
	pin_def_t *step;
	
	step = &st_cfg.m[motor].map->step;
	
    if( st_cfg.m[motor].map->drv.CTRL.ENBL == 1 )
    {
        while( i < 100 )
        {
			pin_set( step );
			wait_ms( 1 );
			pin_reset( step );
			wait_ms( 1 );
			i++;
		}
    }
}

drv8711_t *get_motor_config( const uint8_t motor )
{
    drv8711_t *conf = NULL;

    if( motor > 3 )
        return conf;

    conf = &st_cfg.m[motor].map->drv;
    return conf;
}
