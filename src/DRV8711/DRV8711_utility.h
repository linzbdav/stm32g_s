
#ifndef UTILITY_H_
#define UTILITY_H_

#define REGWRITE	0x00
#define REGREAD		0x80

//typedef enum {false, true} boolean;
typedef enum {low, high} gpio;
//typedef enum {false, true} boolean;

extern bool G_WRITE_ALL_REG;		// Write all registers
extern bool G_READ_ALL_REG;		// Read all registers
extern bool G_RESET_FAULTS;		// Reset all faults
extern bool G_MANUAL_WRITE;		// Manually write SPI data
extern bool G_MANUAL_READ;		// Manually read SPI data

extern unsigned int G_WRITE_ADDR;	// SPI Address
extern unsigned int G_WRITE_DATA;	// SPI Data

extern unsigned int G_READ_ADDR;	// SPI Address
extern unsigned int G_READ_DATA;	// SPI Data

/*
// DRV8711 Registers
extern struct CTRL_Register		G_CTRL_REG;
extern struct TORQUE_Register	G_TORQUE_REG;
extern struct OFF_Register		G_OFF_REG;
extern struct BLANK_Register	G_BLANK_REG;
extern struct DECAY_Register	G_DECAY_REG;
extern struct STALL_Register	G_STALL_REG;
extern struct DRIVE_Register	G_DRIVE_REG;
extern struct STATUS_Register	G_STATUS_REG;
*/

// Function Declarations
void DRV8711_init();
void UpdateDRV8711Registers();
void WriteAllRegisters();
void ReadAllRegisters();
unsigned int SPI_DRV8711_ReadWrite(Stepper_t *st, unsigned char dataHi, unsigned char dataLo);

#endif
