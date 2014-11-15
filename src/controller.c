//---------------------------------------------------------------------------
// Titel        : Stepper Driver STM32F0
//---------------------------------------------------------------------------
// Funktion     : Steuerung eines Steppermotors.
// Schaltung    :
//---------------------------------------------------------------------------
// Hardware     : STM32F051
// Takt         : 48MHz
// Sprache      : ARM C
// Datum        : 20.09.2014
// Version      : 1
// Autor        : David Linzberger
//---------------------------------------------------------------------------
/* Includes */
#include "main.h"
#include "controller.h"
#include "report.h"
#include "commands.h"
#include "usart.h"
#include "switch.h"
/* Private typedef */
/* Private define */
#define DISPATCH(func) if(func == STAT_EAGAIN) return;
/* Private macro */
/* Private variables */
controller_t cs;
extern uint8_t   __BUILD_DATE;
extern uint8_t   __BUILD_NUMBER;
/* Private function prototypes */
static void _controller_HSM();
static stat_t _dispatch_command();
static stat_t _normal_idler();
static stat_t _controller_state();

/* Public functions */
void controller_init()
{
	memset(&cs, 0, sizeof(controller_t));
	controller_init_assertions();
	
	cs.fw_build = (uint32_t) &__BUILD_NUMBER;
	cs.fw_build_date = (uint32_t) &__BUILD_DATE;
	cs.fw_version = FIRMWARE_VERSION;
	cs.hw_platform = HARDWARE_PLATFORM;
	
	cs.comm_mode = TEXT_MODE;
	
	cs.controller_state = CONTROLLER_STARTUP;
}

void controller_init_assertions()
{
	cs.magic_start = MAGICNUM;
	cs.magic_end = MAGICNUM;
}

void controller_run()
{
	while(true)
	{
		_controller_HSM();
	}
}

/* Private functions */
static void _controller_HSM()
{
//----- kernel level ISR handlers ----(flags are set in ISRs)----
	//DISPATCH( hw_hard_reset_handler() );
	//DISPATCH( _limit_switch_handler() );
	DISPATCH( poll_switches() );
	//DISPATCH( _limit_switch_handler() );
	
	//DISPATCH( _system_assertions() );
	
//----- planner hierarchy for gcode and cycles ------------------
	DISPATCH( _controller_state() );
	DISPATCH( _dispatch_command() );
	DISPATCH( _normal_idler() );
}

static stat_t _controller_state()
{
	if( cs.controller_state <= CONTROLLER_STARTUP )
	{
		cs.controller_state = CONTROLLER_READY;
		usart_queue_flush();
		rpt_print_system_ready_message();
	}
	return STAT_OK;
}

static stat_t _dispatch_command()
{
	cmd_handling();
	return STAT_OK;
}

static stat_t _normal_idler()
{
	if( SysTickTimer_getValue() > cs.led_timer )
	{
		cs.led_timer = SysTickTimer_getValue() + LED_NORMAL_TIMER;
		pin_toggle( &hw.ld[0].led );
	}
	
	return STAT_OK;
}

/*
 * _system_assertions() - check memory integrity and other assertions
 */
//#define emergency_system_assertions(a) if((status_code=a) != STAT_OK) return (cm_hard_alarm( status_code ) );

//stat_t _system_assertions()
//{
//	emergency_system_assertions(controller_test_assertions() );
//}
