#include "../commands.h"
#include "../stepper.h"

#define CMDNR 0x09
#define CMDLEN 0x00

// executions
void cmd_reset_motor_exe()
{
    answer.bytes = 1;
    answer.errors = ERROR_NOERROR;
    answer.data[0] = CMDNR;
    answer.index = 0;

	st_reset_motors();

    return;
}

// Command definition struct
cmd_def_t cmd_reset_motor = {
    CMDLEN,
    cmd_reset_motor_exe,
    CMDNR
};
