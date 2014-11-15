#include "main.h"
#include "pins.h"
#include "hardware.h"
#include "usart.h"
#include "spi.h"
#include "gpio.h"

const uint16_t MOTOR_STEP_PIN[MOTORn] = {
	MOTOR_1_STEP_PIN,
	MOTOR_2_STEP_PIN,
	MOTOR_3_STEP_PIN
};

GPIO_TypeDef MOTOR_STEP_PORT[MOTORn] = {
	MOTOR_1_STEP_GPIO_PORT,
	MOTOR_2_STEP_GPIO_PORT,
	MOTOR_3_STEP_GPIO_PORT
};

const uint32_t MOTOR_STEP_CLK[MOTORn] = {
	MOTOR_1_STEP_GPIO_CLK,
	MOTOR_2_STEP_GPIO_CLK,
	MOTOR_3_STEP_GPIO_CLK
};

const uint16_t MOTOR_DIR_PIN[MOTORn] = {
	MOTOR_1_DIR_PIN,
	MOTOR_2_DIR_PIN,
	MOTOR_3_DIR_PIN
};

GPIO_TypeDef MOTOR_DIR_PORT[MOTORn] = {
	MOTOR_1_DIR_GPIO_PORT,
	MOTOR_2_DIR_GPIO_PORT,
	MOTOR_3_DIR_GPIO_PORT
};

const uint32_t MOTOR_DIR_CLK[MOTORn] = {
	MOTOR_1_DIR_GPIO_CLK,
	MOTOR_2_DIR_GPIO_CLK,
	MOTOR_3_DIR_GPIO_CLK
};

const uint16_t MOTOR_RESET_PIN[MOTORn] = {
	MOTOR_1_RESET_PIN,
	MOTOR_2_RESET_PIN,
	MOTOR_3_RESET_PIN
};

GPIO_TypeDef MOTOR_RESET_PORT[MOTORn] = {
	MOTOR_1_RESET_GPIO_PORT,
	MOTOR_2_RESET_GPIO_PORT,
	MOTOR_3_RESET_GPIO_PORT
};

const uint32_t MOTOR_RESET_CLK[MOTORn] = {
	MOTOR_1_RESET_GPIO_CLK,
	MOTOR_2_RESET_GPIO_CLK,
	MOTOR_3_RESET_GPIO_CLK
};

const uint16_t MOTOR_SLEEP_PIN[MOTORn] = {
	MOTOR_1_SLEEP_PIN,
	MOTOR_2_SLEEP_PIN,
	MOTOR_3_SLEEP_PIN
};

GPIO_TypeDef MOTOR_SLEEP_PORT[MOTORn] = {
	MOTOR_1_SLEEP_GPIO_PORT,
	MOTOR_2_SLEEP_GPIO_PORT,
	MOTOR_3_SLEEP_GPIO_PORT
};

const uint32_t MOTOR_SLEEP_CLK[MOTORn] = {
	MOTOR_1_SLEEP_GPIO_CLK,
	MOTOR_2_SLEEP_GPIO_CLK,
	MOTOR_3_SLEEP_GPIO_CLK
};

const uint16_t MOTOR_FAULT_PIN[MOTORn] = {
	MOTOR_1_FAULT_PIN,
	MOTOR_2_FAULT_PIN,
	MOTOR_3_FAULT_PIN
};

GPIO_TypeDef MOTOR_FAULT_PORT[MOTORn] = {
	MOTOR_1_FAULT_GPIO_PORT,
	MOTOR_2_FAULT_GPIO_PORT,
	MOTOR_3_FAULT_GPIO_PORT
};

const uint32_t MOTOR_FAULT_CLK[MOTORn] = {
	MOTOR_1_FAULT_GPIO_CLK,
	MOTOR_2_FAULT_GPIO_CLK,
	MOTOR_3_FAULT_GPIO_CLK
};

const uint16_t MOTOR_STALL_PIN[MOTORn] = {
	MOTOR_1_STALL_PIN,
	MOTOR_2_STALL_PIN,
	MOTOR_3_STALL_PIN
};

GPIO_TypeDef MOTOR_STALL_PORT[MOTORn] = {
	MOTOR_1_STALL_GPIO_PORT,
	MOTOR_2_STALL_GPIO_PORT,
	MOTOR_3_STALL_GPIO_PORT
};

const uint32_t MOTOR_STALL_CLK[MOTORn] = {
	MOTOR_1_STALL_GPIO_CLK,
	MOTOR_2_STALL_GPIO_CLK,
	MOTOR_3_STALL_GPIO_CLK
};

const uint16_t MOTOR_CS_PIN[MOTORn] = {
	EVAL_CS0_PIN,
	EVAL_CS1_PIN,
	EVAL_CS2_PIN,
};

GPIO_TypeDef MOTOR_CS_PORT[MOTORn] = {
	EVAL_CS0_GPIO_PORT,
	EVAL_CS1_GPIO_PORT,
	EVAL_CS2_GPIO_PORT
};

hwSingleton_t hw;

static void _led_init();
//static void _I2C_init();
//static void _COM_init();
//static void _SPI_init();
static void _MOT_init();
static void _SWITCH_init();

void hardware_init()
{
	pinout_config();
	
	// LED init
	_led_init();

	// Comminication Init
	// I2C init
	//_I2C_init();

	usart_init();
	spi_init();

	// Motor init
	_MOT_init();
	
	// Switch init
	_SWITCH_init();

}

static void _SWITCH_init()
{
	hw.sw[0].sw.port = AXIS_X_MAX_GPIO_PORT;
	hw.sw[0].sw.pin  = AXIS_X_MAX_PIN;
	hw.sw[1].sw.port = AXIS_X_MIN_GPIO_PORT;
	hw.sw[1].sw.pin  = AXIS_X_MIN_PIN;
	
	hw.sw[2].sw.port = AXIS_Y_MAX_GPIO_PORT;
	hw.sw[2].sw.pin  = AXIS_Y_MAX_PIN;
	hw.sw[3].sw.port = AXIS_Y_MIN_GPIO_PORT;
	hw.sw[3].sw.pin  = AXIS_Y_MIN_PIN;
	
	hw.sw[4].sw.port = AXIS_Z_MAX_GPIO_PORT;
	hw.sw[4].sw.pin  = AXIS_Z_MAX_PIN;
	hw.sw[5].sw.port = AXIS_Z_MIN_GPIO_PORT;
	hw.sw[5].sw.pin  = AXIS_Z_MIN_PIN;
}

static void _MOT_init()
{
	uint8_t i;
	for( i = MOTOR1; i < MOTORn; i++ )
	{
		hw.st[i].step.pin 	= MOTOR_STEP_PIN[ i ];
		hw.st[i].step.port 	= MOTOR_STEP_PORT[ i ];
		hw.st[i].dir.pin	= MOTOR_DIR_PIN[ i ];
		hw.st[i].dir.port	= MOTOR_DIR_PORT[ i ];
		hw.st[i].reset.pin	= MOTOR_RESET_PIN[ i ];
		hw.st[i].reset.port = MOTOR_RESET_PORT[ i ];
		hw.st[i].sleep.pin 	= MOTOR_SLEEP_PIN[ i ];
		hw.st[i].sleep.port = MOTOR_SLEEP_PORT[ i ];
		hw.st[i].fault.pin	= MOTOR_FAULT_PIN[ i ];
		hw.st[i].fault.port = MOTOR_FAULT_PORT[ i ];
		hw.st[i].stall.pin	= MOTOR_STALL_PIN[ i ];
		hw.st[i].stall.port = MOTOR_STALL_PORT[ i ];
		hw.st[i].spi_cs.pin	= MOTOR_CS_PIN[ i ];
		hw.st[i].spi_cs.port= MOTOR_CS_PORT[ i ];
		hw.st[i].spi = SPI2_BASE;
	}
}

static void _led_init()
{
	hw.ld[0].led.pin = LED1_PIN;
	hw.ld[0].led.port = LED1_PORT;
}
