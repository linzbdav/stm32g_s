BINARY = main

DEVICE = stm32f051c8t6

SRCS = 	main.c \
		controller.c \
		gpio.c \
		hardware.c \
		commands.c \
		DRV8711/DRV8711_utility.c \
		pins.c \
		spi.c \
		usart.c \
		util.c \
		report.c \
		switch.c \
		cmds/cmd_add_dwell.c \
		cmds/cmd_add_segment.c \
		cmds/cmd_check_com_status.c \
		cmds/cmd_get_motor_config.c \
		cmds/cmd_motor_enable.c \
		cmds/cmd_motor_step.c \
		cmds/cmd_set_motor_microstep.c \
		cmds/cmd_set_motor_torque.c \
		cmds/cmd_switch_led.c \
		cmds/cmd_reset_motor.c \
		lib/cbuff.c \
		stepper.c
		

LDSCRIPT = stm32f0-discovery.ld

OOCD_INTERFACE = stlink-v2
OOCD_BOARD = stm32f0discovery

include Makefile.include
