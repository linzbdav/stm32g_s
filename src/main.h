#ifndef __MAIN_H_
#define __MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/spi.h>
#include <libopencm3/stm32/f0/nvic.h>
#include <libopencm3/stm32/dma.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/flash.h>

// libs
#include "lib/cbuff.h"

#include "pins.h"
#include "hardware.h"

#define FIRMWARE_BUILD		1
#define FIRMWARE_VERSION	1
#define HARDWARE_PLATFORM	1

#define MAGICNUM 123456

#define magic_t uint32_t

#define AXIS_X 0
#define AXIS_Y 1
#define AXIS_Z 2

enum STATUS_e
{
	STAT_OK = 0,
	STAT_ERROR,
	STAT_EAGAIN,
	STAT_NOOP,
	STAT_COMPLETE,
	STAT_TERMINATE,
	STAT_RESET,
	STAT_BUFFER_EMPTY,
	STAT_BUFFER_FULL,
	STAT_BUFFER_FULL_FATAL,
	STAT_INITIALIZING,
	STAT_ERROR_17,
	STAT_INTERNAL_ERROR,
	STAT_STEPPER_ASSERTION_FAILURE
};
typedef enum STATUS_e stat_t;

//#define NULL    0L
#define conv_8to16(a,b)	( ( ( (uint16_t)a ) << 8 ) | ((uint16_t)b ) )


uint8_t prints_mem( void const *vp, uint8_t n, uint8_t *buf, uint8_t max_len );

uint32_t SysTickTimer_getValue();
void wait_ms( uint8_t time );

// ------------------ config.h ---------------
enum tgCommunicationMode {
	TEXT_MODE = 0,
	JSON_MODE,
	JSON_MODE_RELAXED
};

#endif // __MAIN_H_
