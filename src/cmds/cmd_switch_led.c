#include "../main.h"
#include "../commands.h"

#define CMDNR 0x01
#define CMDLEN 0x00

// executions
void cmd_switch_led_exe()
{
	pin_toggle( &hw.ld[LED1].led );

    answer.bytes = 2;
    answer.errors = ERROR_NOERROR;
    answer.data[0] = CMDNR;
    answer.data[1] = pin_getState( LED1 );
    answer.index = 0;

    return;
}

// Command definition struct
cmd_def_t cmd_switch_led = {
    CMDLEN,
    cmd_switch_led_exe,
    CMDNR
};

