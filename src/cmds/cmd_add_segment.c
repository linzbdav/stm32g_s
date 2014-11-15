#include "../commands.h"

#define CMDNR 0x02
#define CMDLEN 0x07

// executions
void cmd_add_segment_exe()
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
		sw->direction[0] = ( command.data[0] >> 7 ) & 0x01;
		sw->direction[1] = ( command.data[1] >> 7 ) & 0x01;
		sw->direction[2] = ( command.data[2] >> 7 ) & 0x01;

		sw->position[0] = ( (frac)( command.data[3] & 0x7F ) ) << 7;
		sw->position[1] = ( (frac)( command.data[4] & 0x7F ) ) << 7;
		sw->position[2] = ( (frac)( command.data[5] & 0x7F ) ) << 7;

		sw->time = (frac)(conv_8to16( command.data[6], command.data[7] ) ) << 2;

		se_queue_write_buffer( MOVE_TYPE_ALINE );

    	st_request_prep_move();

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
cmd_def_t cmd_add_segment = {
    CMDLEN,
    cmd_add_segment_exe,
    CMDNR
};
