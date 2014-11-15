#ifndef __STEPPER_H_
#define __STEPPER_H_

#include "hardware.h"

#define FREQUENCY_DDA 50000

enum motorPowerState
{
	MOTOR_OFF = 0,
	MOTOR_IDLE,
	MOTOR_RUNNING,
	MOTOR_POWER_TIMEOUT_START,
	MOTOR_POWER_TIMEOUT_COUNTDOWN
};

enum cmMotorPowerMode
{
	MOTOR_DISABLED = 0,
	MOTOR_ALWAYS_POWERED,
	MOTOR_POWERED_IN_CYCLE,
	MOTOR_POWERED_ONLY_WHEN_MOVING,
	MOTOR_POWER_MODE_MAX_VALUE
};

enum prepBufferState
{
	PREP_BUFFER_OWNED_BY_LOADER,
	PREP_BUFFER_OWNED_BY_EXEC
};

// config structure
typedef struct cfgMotor
{
	uint8_t microsteps;		// microsteps to apply for each axis
	uint8_t polarity;		// 0=normal polarity, 1=reverse motor direction
	uint8_t power_mode;
	uint32_t power_level;
	uint32_t step_angle;		// degrees per whole step ( ex. 1.8 )
	uint32_t travel_rev;		// mm or deg of travel per motor revolution
	uint32_t steps_per_unit;	// steps (usteps)/mm or deg of travel
	uint32_t units_per_step;

	// private
	float power_level_scaled;
	Stepper_t *map;
} cfgMotor_t;

typedef struct stConfig
{
	uint32_t motor_idle_timeout;
	cfgMotor_t m[MOTORn];
} stConfig_t;

// Runtime structure. Used only from the ISR
typedef struct stRunMotor
{
	uint32_t substep_increment;
	int32_t substep_accumulator;
	uint8_t power_state;
	uint32_t power_systick;
	uint32_t power_level_dynamic;
} stRunMotor_t;

typedef struct stRunSingleton
{
	magic_t magic_start;
	int32_t dda_ticks_downcount;
	int32_t dda_ticks_X_substeps;
	stRunMotor_t m[MOTORn];
	magic_t	magic_end;
} stRunSingleton_t;

// Prep-time structure
// TODO: Change to PING / PONG
typedef struct stPrepMotor
{
	uint32_t substep_increment;
	// direction and direction change
	uint8_t direction;
	uint8_t prev_direction;
	int8_t step_sign;
	// following error correction
	int32_t correction_holdoff;
	uint32_t corrected_steps;
	// accumulator phase correction
	uint32_t prev_segment_time;
	uint32_t accumulator_correction;
	uint8_t accumulator_correction_flag;
} stPrepMotor_t;

typedef struct stPrepSingleton
{
	magic_t magic_start;
	uint8_t move_type;
	volatile uint8_t exec_state;
	uint32_t dda_period;
	uint32_t dda_ticks;
	uint32_t dda_ticks_X_substeps;
	stPrepMotor_t m[MOTORn];
	magic_t magic_end;
} stPrepSingleton_t;

extern stConfig_t st_cfg;
extern stPrepSingleton_t st_prep;

void stepper_init();
void stepper_init_assertions();
uint8_t stepper_test_assertions();
uint16_t st_get_status();
void st_prep_null();
void st_request_prep_move();
void st_reset_motors();
void st_deenergize_motors();
void st_energize_motors();

void st_set_motor_torque( uint8_t motor, uint8_t torque );
void st_set_motor_microstep( uint8_t motor, uint16_t microstep );
void st_step_motor( uint8_t motor );
void st_enable_motor( uint8_t motor );
void st_disable_motor( uint8_t motor );


drv8711_t *get_motor_config( const uint8_t motor );

#endif // __STEPPER_H_
