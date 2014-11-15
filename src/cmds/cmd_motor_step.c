#include "../commands.h"
#include "../stepper.h"

#define CMDNR   0x07
#define CMDLEN  0x01

// executions
void cmd_motor_step_exe()
{
    if( command.data[0] > 3 )
    {
        answer.bytes = 15;
		answer.errors = ERROR_ERROR;
		answer.data[0] = CMDNR;
		answer.data[1] = 'N';
		answer.data[2] = 'O';
		answer.data[3] = 'T';
		answer.data[4] = 'A';
		answer.data[5] = 'V';
		answer.data[6] = 'A';
		answer.data[7] = 'L';
		answer.data[8] = 'I';
		answer.data[9] = 'D';
		answer.data[10] = 'M';
		answer.data[11] = 'O';
		answer.data[12] = 'T';
		answer.data[13] = 'O';
		answer.data[14] = 'R';
		answer.index = 0;
		return;
    }

    st_step_motor( command.data[0] );

    answer.bytes = 1;
    answer.errors = ERROR_NOERROR;
    answer.data[0] = CMDNR;
    answer.index = 0;

	return;
}

// Command definition struct
cmd_def_t cmd_motor_step = {
    CMDLEN,
    cmd_motor_step_exe,
    CMDNR
};
