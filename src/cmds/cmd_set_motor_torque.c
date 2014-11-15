#include "../commands.h"

#define CMDNR   0x05
#define CMDLEN  0x02

// executions
void cmd_set_motor_torque_exe()
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

    //st_set_motor_torque( command.data[0], command.data[1] );

    answer.bytes = 1;
    answer.errors = ERROR_NOERROR;
    answer.data[0] = CMDNR;

    answer.index = 0;

	return;
}

// Command definition struct
cmd_def_t cmd_set_motor_torque = {
    CMDLEN,
    cmd_set_motor_torque_exe,
    CMDNR
};

