#include "main.h"
#include "report.h"
#include "controller.h"
#include "usart.h"

void _startup_helper( stat_t status, const char *mst )
{
#ifndef __SUPPRESS_STARTUP_MESSAGES
	
#endif
}

void rpt_print_system_ready_message()
{
	_startup_helper( STAT_OK, "SYSTEM READY" );
	if( cs.comm_mode == TEXT_MODE )
	{
		text_response( STAT_OK, (uint8_t *)"");
	}
}

static uint8_t promt_ok[] = "tinyg [mm] ok> ";
static uint8_t promt_err[]= "tinyg [mm] err:";

void text_response( const stat_t status, uint8_t *buf )
{	
	if( ( status == STAT_OK ) || ( status == STAT_EAGAIN ) || ( status == STAT_NOOP ))
	{
		serial_send( promt_ok, 15 );
	}
	else
	{
		serial_send( promt_err, 15 );
	}
}
