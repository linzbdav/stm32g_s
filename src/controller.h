#ifndef CONTROLLER_H_ONCE
#define CONTROLLER_H_ONCE

#define LED_NORMAL_TIMER 500

typedef struct controllerSingleton
{
	magic_t magic_start;

	// system identification values
	uint16_t fw_build;
	uint16_t fw_version;
	uint16_t fw_build_date;
	uint16_t config_version;
	uint16_t hw_platform;
	uint16_t hw_version;
	
	// communications state variables
	uint8_t comm_mode;
	
	uint8_t controller_state;
	uint32_t led_timer;
	
	magic_t magic_end;
} controller_t;

extern controller_t cs;

enum cmControllerState {			// manages startup lines
	CONTROLLER_INITIALIZING = 0,	// controller is initializing - not ready for use
	CONTROLLER_NOT_CONNECTED,		// controller has not yet detected connection to USB (or other communication)
	CONTROLLER_CONNECTED,			// controller has connected to USB (or other comm channel)
	CONTROLLER_STARTUP,				// controller is running startup messages and lines
	CONTROLLER_READY				// controller is active and ready for use
};

/* function prototypes */
void controller_init();
void controller_init_assertions();
void controller_run();

#endif
