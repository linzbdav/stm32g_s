#ifndef __COMMANDS_H_
#define __COMMANDS_H_
#include "main.h"
#include "error.h"

#define COMMAND_MAX_LENGTH  255
#define ANSWER_MAX_LENGTH   255

#define CMDDC_IDLE          0
#define CMDDC_CMD           1
#define CMDDC_DATA          2
#define CMDDC_CHKSUM        3
#define CMDDC_ANSWER        4

int execure_cmd( int i_cmd );
void cmd_handling( void );

// Command definition struct
typedef struct cmd_def_struct cmd_def_t;
struct cmd_def_struct
{
    uint16_t bytes;
    void ( *execute )(); // Command
    uint16_t number;     // Command Number
};

typedef struct answer_struct answer_t;
struct answer_struct
{
    uint16_t index;
    uint16_t bytes;
    uint8_t data[COMMAND_MAX_LENGTH];
    uint16_t errors;
};

// Definition Command Struct
typedef struct command_struct command_t;
struct command_struct
{
    uint8_t adresse;    // Adresse
    uint16_t number;    // Command number
    uint16_t bytes;     // Command length
    uint8_t data[COMMAND_MAX_LENGTH]; // Data
    uint16_t index;     // Data index
    uint16_t port_fd;   // Active port
    uint8_t checksum;   // Checksum
};

extern command_t command;
extern answer_t answer;
extern volatile int32_t SerialCommsTimer;

#endif // __COMMANDS_H_
