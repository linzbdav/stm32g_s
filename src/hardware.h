#ifndef __HARDWARE_H_
#define __HARDWARE_H_

#define SPI_TypeDef uint32_t

#include "pins.h"
#include "DRV8711/DRV8711_registers.h"

#undef 	HSE_VALUE
#define HSE_VALUE ((uint32_t)16000000)

// Pin assignments
#define LED1_PIN    				GPIO15
#define LED1_PORT					GPIOC

// Communications support
// I2C
#define EVAL_I2C					I2C1
#define EVAL_I2C_CLK				RCC_APB1Periph_I2C1

#define EVAL_I2C_SCL_PIN			GPIO8
#define EVAL_I2C_SCL_GPIO_PORT	    GPIOB
#define EVAL_I2C_SCL_GPIO_CLK		RCC_AHBPeriph_GPIOB
#define EVAL_I2C_SCL_SOURCE			GPIO_PinSource8
#define EVAL_I2C_SCL_AF				GPIO_AF_1

#define EVAL_I2C_SDA_PIN			GPIO9
#define EVAL_I2C_SDA_GPIO_PORT	    GPIOB
#define EVAL_I2C_SDA_GPIO_CLK		RCC_AHBPeriph_GPIOB
#define EVAL_I2C_SDA_SOURCE			GPIO_PinSource9
#define EVAL_I2C_SDA_AF				GPIO_AF_1
// USART
#define EVAL_COM1					USART1
#define EVAL_COM1_CLK				RCC_APB2Periph_USART1

#define EVAL_COM1_TX_PIN			GPIO6
#define EVAL_COM1_TX_GPIO_PORT	    GPIOB
#define EVAL_COM1_TX_GPIO_CLK		RCC_AHBPeriph_GPIOB
#define EVAL_COM1_TX_SOURCE			GPIO_PinSource6
#define EVAL_COM1_TX_AF				GPIO_AF_0

#define EVAL_COM1_RX_PIN			GPIO7
#define EVAL_COM1_RX_GPIO_PORT	    GPIOB
#define EVAL_COM1_RX_GPIO_CLK		RCC_AHBPeriph_GPIOB
#define EVAL_COM1_RX_SOURCE			GPIO_PinSource7
#define EVAL_COM1_RX_AF				GPIO_AF_0

#define EVAL_COM1_IRQn				USART1_IRQn
// SPI
#define EVAL_SPI					SPI2
#define EVAL_SPI_CLK				RCC_APB1Periph_SPI2

#define EVAL_SPI_SCK_PIN			GPIO13
#define EVAL_SPI_SCK_GPIO_PORT	    GPIOB
#define EVAL_SPI_SCK_GPIO_CLK		RCC_AHBPeriph_GPIOB
#define EVAL_SPI_SCK_SOURCE			GPIO_PinSources13
#define EVAL_SPI_SCK_AF				GPIO_AF_0

#define EVAL_SPI_MISO_PIN			GPIO14
#define EVAL_SPI_MISO_GPIO_PORT	    GPIOB
#define EVAL_SPI_MISO_GPIO_CLK	    RCC_AHBPeriph_GPIOB
#define EVAL_SPI_MISO_SOURCE		GPIO_PinSources14
#define EVAL_SPI_MISO_AF			GPIO_AF_0

#define EVAL_SPI_MOSI_PIN			GPIO15
#define EVAL_SPI_MOSI_GPIO_PORT	    GPIOB
#define EVAL_SPI_MOSI_GPIO_CLK	    RCC_AHBPeriph_GPIOB
#define EVAL_SPI_MOSI_SOURCE		GPIO_PinSources15
#define EVAL_SPI_MOSI_AF			GPIO_AF_0

#define EVAL_CS0_PIN				GPIO12
#define EVAL_CS0_GPIO_PORT			GPIOB
#define EVAL_CS0_GPIO_CLK			RCC_AHBPeriph_GPIOB

#define EVAL_CS1_PIN				GPIO0
#define EVAL_CS1_GPIO_PORT			GPIOA
#define EVAL_CS1_GPIO_CLK			RCC_AHBPeriph_GPIOA

#define EVAL_CS2_PIN				GPIO14
#define EVAL_CS2_GPIO_PORT			GPIOC
#define EVAL_CS2_GPIO_CLK			RCC_AHBPeriph_GPIOC

// Stepper pins
// Motor 1
#define MOTOR_1_STEP_PIN			GPIO8
#define MOTOR_1_STEP_GPIO_PORT	    GPIOA
#define MOTOR_1_STEP_GPIO_CLK		RCC_GPIOA

#define MOTOR_1_DIR_PIN				GPIO9
#define MOTOR_1_DIR_GPIO_PORT		GPIOA
#define MOTOR_1_DIR_GPIO_CLK		RCC_GPIOA

#define MOTOR_1_RESET_PIN			GPIO11
#define MOTOR_1_RESET_GPIO_PORT	    GPIOB
#define MOTOR_1_RESET_GPIO_CLK	    RCC_GPIOB

#define MOTOR_1_SLEEP_PIN			GPIO10
#define MOTOR_1_SLEEP_GPIO_PORT	    GPIOB
#define MOTOR_1_SLEEP_GPIO_CLK	    RCC_GPIOB

#define MOTOR_1_FAULT_PIN			GPIO2
#define MOTOR_1_FAULT_GPIO_PORT	    GPIOB
#define MOTOR_1_FAULT_GPIO_CLK	    RCC_GPIOB

#define MOTOR_1_STALL_PIN			GPIO1
#define MOTOR_1_STALL_GPIO_PORT	    GPIOB
#define MOTOR_1_STALL_GPIO_CLK	    RCC_GPIOB
// MOTOR 2
#define MOTOR_2_STEP_PIN			GPIO15
#define MOTOR_2_STEP_GPIO_PORT	    GPIOA
#define MOTOR_2_STEP_GPIO_CLK		RCC_GPIOA

#define MOTOR_2_DIR_PIN				GPIO3
#define MOTOR_2_DIR_GPIO_PORT		GPIOB
#define MOTOR_2_DIR_GPIO_CLK		RCC_GPIOB

#define MOTOR_2_RESET_PIN			GPIO7
#define MOTOR_2_RESET_GPIO_PORT	    GPIOA
#define MOTOR_2_RESET_GPIO_CLK	    RCC_GPIOA

#define MOTOR_2_SLEEP_PIN			GPIO0
#define MOTOR_2_SLEEP_GPIO_PORT	    GPIOB
#define MOTOR_2_SLEEP_GPIO_CLK	    RCC_GPIOB

#define MOTOR_2_FAULT_PIN			GPIO6
#define MOTOR_2_FAULT_GPIO_PORT	    GPIOA
#define MOTOR_2_FAULT_GPIO_CLK	    RCC_GPIOA

#define MOTOR_2_STALL_PIN			GPIO5
#define MOTOR_2_STALL_GPIO_PORT	    GPIOA
#define MOTOR_2_STALL_GPIO_CLK	    RCC_GPIOA
// MOTOR 3
#define MOTOR_3_STEP_PIN			GPIO4
#define MOTOR_3_STEP_GPIO_PORT	    GPIOB
#define MOTOR_3_STEP_GPIO_CLK		RCC_GPIOB

#define MOTOR_3_DIR_PIN				GPIO5
#define MOTOR_3_DIR_GPIO_PORT		GPIOB
#define MOTOR_3_DIR_GPIO_CLK		RCC_GPIOB

#define MOTOR_3_RESET_PIN			GPIO3
#define MOTOR_3_RESET_GPIO_PORT	    GPIOA
#define MOTOR_3_RESET_GPIO_CLK	    RCC_GPIOA

#define MOTOR_3_SLEEP_PIN			GPIO4
#define MOTOR_3_SLEEP_GPIO_PORT	    GPIOA
#define MOTOR_3_SLEEP_GPIO_CLK	    RCC_GPIOA

#define MOTOR_3_FAULT_PIN			GPIO2
#define MOTOR_3_FAULT_GPIO_PORT	    GPIOA
#define MOTOR_3_FAULT_GPIO_CLK	    RCC_GPIOA

#define MOTOR_3_STALL_PIN			GPIO1
#define MOTOR_3_STALL_GPIO_PORT	    GPIOA
#define MOTOR_3_STALL_GPIO_CLK	    RCC_GPIOA
// Endstops pins
#define AXIS_X_MIN_PIN				GPIO10
#define AXIS_X_MIN_GPIO_PORT		GPIOA
#define AXIS_X_MIN_GPIO_CLK			RCC_GPIOA

#define AXIS_X_MAX_PIN				GPIO11
#define AXIS_X_MAX_GPIO_PORT		GPIOA
#define AXIS_X_MAX_GPIO_CLK			RCC_GPIOA

#define AXIS_Y_MIN_PIN				GPIO12
#define AXIS_Y_MIN_GPIO_PORT		GPIOA
#define AXIS_Y_MIN_GPIO_CLK			RCC_GPIOA


#define AXIS_Y_MAX_PIN				GPIO7
#define AXIS_Y_MAX_GPIO_PORT		GPIOF
#define AXIS_Y_MAX_GPIO_CLK			RCC_GPIOF


#define AXIS_Z_MIN_PIN				GPIO6
#define AXIS_Z_MIN_GPIO_PORT		GPIOF
#define AXIS_Z_MIN_GPIO_CLK			RCC_GPIOF


#define AXIS_Z_MAX_PIN				GPIO13
#define AXIS_Z_MAX_GPIO_PORT		GPIOC
#define AXIS_Z_MAX_GPIO_CLK			RCC_GPIOC

enum LED_TypeDef {
    LED1 = 0,
    LEDn
};

enum MOTOR_TypeDef {
    MOTOR1 = 0,
    MOTOR2,
    MOTOR3,
    MOTORn
};

enum SWITCH_TypeDef {
    SWITCH1 = 0,
    SWITCH2,
    SWITCH3,
    SWITCH4,
    SWITCH5,
    SWITCH6,
    SWITCHn
};

typedef struct {
	pin_def_t	step;
	pin_def_t	dir;
	pin_def_t	reset;
	pin_def_t	sleep;
	pin_def_t	fault;
	pin_def_t	stall;
	pin_def_t   spi_cs;
	SPI_TypeDef spi;
	drv8711_t   drv;
} Stepper_t;

typedef struct {
	pin_def_t led;
} Led_t;

typedef struct {
    pin_def_t sw;
} Switch_t;

typedef struct hwSingleton {
    Stepper_t st[MOTORn];
    Switch_t  sw[SWITCHn];
    Led_t     ld[LEDn];
} hwSingleton_t;

extern hwSingleton_t hw;

void hardware_init();

// Function from DRV8711.c
void DRV8711_Write_Reg( uint8_t reg, Stepper_t *st );
uint16_t DRV8711_Read_Reg( uint8_t reg, Stepper_t *st );

#endif
