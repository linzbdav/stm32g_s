//---------------------------------------------------------------------------
// Titel        : Stepper Driver STM32F0
//---------------------------------------------------------------------------
// Funktion     : Befehle an den Schrittmotor treiber
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
#include "commands.h"
#include "usart.h"

extern cmd_def_t cmd_check_com_status;      // 0x00
extern cmd_def_t cmd_switch_led;            // 0x01
extern cmd_def_t cmd_add_segment;           // 0x02
extern cmd_def_t cmd_add_dwell;             // 0x03
extern cmd_def_t cmd_get_motor_config;      // 0x04
extern cmd_def_t cmd_set_motor_torque;      // 0x05
extern cmd_def_t cmd_set_motor_microstep;   // 0x06
extern cmd_def_t cmd_motor_step;            // 0x07
extern cmd_def_t cmd_motor_enable;          // 0x08
extern cmd_def_t cmd_reset_motor;			// 0x09

uint8_t buffer[ANSWER_MAX_LENGTH];
volatile int32_t SerialCommsTimer;

command_t command;
answer_t answer;

const cmd_def_t *cmd_defs[] = {
    &cmd_check_com_status,
    &cmd_switch_led,
    &cmd_add_segment,
    &cmd_add_dwell,
    &cmd_get_motor_config,
    &cmd_set_motor_torque,
    &cmd_set_motor_microstep,
    &cmd_motor_step,
    &cmd_motor_enable,
    &cmd_reset_motor,
    0   // Last must always be NULL
};

int cmd_from_nr( uint8_t cmd, command_t *c, uint16_t port_fd )
{
    c->port_fd = port_fd;
    c->number = 0xFF;
    c->index = 0;
    c->checksum = cmd;
    c->bytes = 0;

    // Find command and determine bytes
    int i = 0;
    while( cmd_defs[i] )
    {
        if( cmd_defs[i]->number == cmd )
        {
            c->bytes = cmd_defs[i]->bytes;
            c->number = cmd;
            return c->bytes;
        }
        i++;
    }
    return -1;
}

int execute_cmd( int i_cmd )
{
    int i = 0;

    while( cmd_defs[i] )
    {
        if( cmd_defs[i]->number == i_cmd )
        {
            cmd_defs[i]->execute();
            return 1;
        }
        i++;
    }
    return 0;
}

void cmd_handling( void )
{
    static uint8_t state = CMDDC_IDLE;
    static int8_t ret = 0;
    static uint8_t rec_char;
    static uint8_t active = 0;

    uint8_t i;
    uint8_t crc;

    switch( state )
    {
    case CMDDC_IDLE:
        if( serial_read( &rec_char ) )
        {
            SerialCommsTimer = 1000;
            if( rec_char == ADRESSE )
            {
                active = 1;
            }
            else
            {
                active = 0;
            }
            state = CMDDC_CMD;
        }
        break;

    case CMDDC_CMD:
        if( serial_read( &rec_char ) )
        {
            SerialCommsTimer = 1000;
            ret = cmd_from_nr( rec_char, &command, 0 );

            if( ret > 0 )
            {
                state = CMDDC_DATA;
            }
            else if( ret == 0 )
            {
                state = CMDDC_CHKSUM;
            }
            else
            {
                answer.bytes = 1;
                answer.errors = ERROR_ERROR;
                answer.data[0] = ERROR_COMMAND;
                state = CMDDC_ANSWER;
            }
        }
        break;

    case CMDDC_DATA:
        if( serial_read( &rec_char ) )
        {
            SerialCommsTimer = 1000;
            command.data[command.index] = rec_char;
            command.index++;
            command.checksum ^= rec_char;
            if( command.index == command.bytes )
            {
                state = CMDDC_CHKSUM;
            }
        }
        break;

    case CMDDC_CHKSUM:
        if( serial_read( &rec_char ) )
        {
            if( command.checksum == rec_char )
            {
                if( active )
                {
                    execute_cmd( command.number );
                }
            }
            else
            {
                answer.bytes = 1;
                answer.errors = ERROR_ERROR;
                answer.data[0] = ERROR_CHECKSUM;
            }
            
            SerialCommsTimer = 1000;
            state = CMDDC_ANSWER;
        }
        break;

    case CMDDC_ANSWER:
        ret = 0;
        buffer[ret++] = ADRESSE;
        crc = 0;
        buffer[ret++] = answer.errors;
        crc ^= answer.errors;
        buffer[ret++] = answer.bytes;
        crc ^= answer.bytes;
        for( i = 0; i < answer.bytes; i++ )
        {
			buffer[ret++] = answer.data[i];
            crc ^= answer.data[i];
        }
        buffer[ret++] = crc;

        serial_send( &buffer[0], ret );

        active = 0;
        state = CMDDC_IDLE;
        break;

    default:
        SerialCommsTimer = 0;
        break;
    }

    if( SerialCommsTimer == 0 )
    {
        active = 0;
        state = CMDDC_IDLE;
		SerialCommsTimer = 100;
    }
}
