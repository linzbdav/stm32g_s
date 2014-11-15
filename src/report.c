//---------------------------------------------------------------------------
// Titel        : Stepper Driver STM32F0
//---------------------------------------------------------------------------
// Funktion     : Report Funktionen des Schrittmotortreibers 
// Schaltung    :
//---------------------------------------------------------------------------
// Hardware     : STM32F051
// Takt         : 48MHz
// Sprache      : ARM C
// Datum        : 14.11.2014
// Version      : 1
// Autor        : David Linzberger
//---------------------------------------------------------------------------
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
