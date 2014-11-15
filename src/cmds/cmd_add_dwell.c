#include "../commands.h"

#define CMDNR 0x03
#define CMDLEN 0x02

// executions
void cmd_add_dwell_exe()
{
	/*
	seg_def_t *sw = NULL;

	sw = se_get_write_buffer();
	if( sw == NULL )
	{
		answer.bytes = 3;
		answer.errors = ERROR_ERROR;
		answer.data[0] = CMDNR;
		answer.data[1] = 'O';
		answer.data[2] = 'K';
		answer.index = 0;
	}
	else
	{
		sw->direction[0] = 0;
		sw->direction[1] = 0;
		sw->direction[2] = 0;

		sw->position[0] = 0;
		sw->position[1] = 0;
		sw->position[2] = 0;

		sw->time = (frac)(conv_8to16( command.data[0], command.data[1] ) ) << 2;

		se_queue_write_buffer( MOVE_TYPE_DWELL );

		answer.bytes = 3;
		answer.errors = ERROR_NOERROR;
		answer.data[0] = CMDNR;
		answer.data[1] = 'O';
		answer.data[2] = 'K';
		answer.index = 0;
	}
	*/
	answer.bytes = 3;
	answer.errors = ERROR_NOERROR;
	answer.data[0] = CMDNR;
	answer.data[1] = 'O';
	answer.data[2] = 'K';
	answer.index = 0;
	
	return;
}

// Command definition struct
cmd_def_t cmd_add_dwell = {
    CMDLEN,
    cmd_add_dwell_exe,
    CMDNR
};
