#include "../commands.h"
#include "../controller.h"

#define CMDNR 0x00
#define CMDLEN 0x00

// executions
void cmd_check_com_status_exe()
{
	
	//uint16_t status = st_get_status();
    //answer.data[1] = ( status >> 8 );
    //answer.data[2] = status;
	
    answer.bytes = 9;
    answer.errors = ERROR_NOERROR;
    answer.data[0] = CMDNR;
    answer.data[1] = ( cs.fw_build >> 8 ) & 0x00FF;
    answer.data[2] = cs.fw_build & 0x00FF;
    answer.data[3] = ( cs.fw_build_date >> 8 ) & 0x00FF;
    answer.data[4] = cs.fw_build_date & 0x00FF;
    answer.data[5] = ( cs.fw_version >> 8 ) & 0x00FF;
    answer.data[6] = cs.fw_version & 0x00FF;
    answer.data[7] = ( cs.hw_platform >> 8 ) & 0x00FF;
    answer.data[8] = cs.hw_platform & 0x00FF;
    answer.index = 0;

    return;
}

// Command definition struct
cmd_def_t cmd_check_com_status = {
    CMDLEN,
    cmd_check_com_status_exe,
    CMDNR
};
