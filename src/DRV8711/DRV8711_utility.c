/*******************************************************************************
 *
 *  DRV8711_utility.c - Definition file for utility functions
 *  David Linzberger
 *  DRV8711_FIRMWARE
 *  10/03/2014
 *
 ******************************************************************************/
#include "../main.h"
#include "../spi.h"
#include "../stepper.h"

#include "DRV8711_registers.h"
#include "DRV8711_utility.h"

 /*****************************************************************************/

// Define Global Variables
struct CTRL_Register G_CTRL_REG;
struct TORQUE_Register G_TORQUE_REG;
struct OFF_Register G_OFF_REG;
struct BLANK_Register G_BLANK_REG;
struct DECAY_Register G_DECAY_REG;
struct STALL_Register G_STALL_REG;
struct DRIVE_Register G_DRIVE_REG;
struct STATUS_Register G_STATUS_REG;

bool G_WRITE_ALL_REG;		// Write all registers
bool G_READ_ALL_REG;		// Read all registers
bool G_RESET_FAULTS;		// Reset all faults
bool G_MANUAL_WRITE;		// Manually write SPI data
bool G_MANUAL_READ;		// Manually read SPI data

unsigned int G_WRITE_ADDR;	// SPI Address
unsigned int G_WRITE_DATA;	// SPI Data

unsigned int G_READ_ADDR;	// SPI Address
unsigned int G_READ_DATA;	// SPI Data

/*****************************************************************************/

// Function Definitions
void DRV8711_init( Stepper_t *st )
{
	// Set Default GPIO Settings
	pin_reset( &st->sleep );	// Set sleep pin to low
	pin_reset( &st->reset );	// Set reset pin to low
	pin_reset( &st->step );		// Set step pin to low
	pin_reset( &st->dir );		// Set dir pin to low
//	pin_set( st->fault );
//	pin_set( st->stall );
	pin_reset( &st->spi_cs );	// Set Spi Cs to low

	// Set Default Register Settings
	// CTRL Register
/*
	st->drv.CTRL_Register.Address = REG_CTRL;
	st->drv.CTRL_Register.DTIME = DRV8711_DTIME_850;
	st->drv.CTRL_Register.ISGAIN = DRV8711_ISGAIN_40;
	st->drv.CTRL_Register.EXSTALL = 0x00;
	st->drv.CTRL_Register.MODE = 0x03;
	st->drv.CTRL_Register.RSTEP = 0x00;
	st->drv.CTRL_Register.RDIR = 0x00;
	st->drv.CTRL_Register.ENBL = 0x01;
*/
	G_CTRL_REG.Address 	= REG_CTRL;
	G_CTRL_REG.DTIME 	= DRV8711_DTIME_850;
	G_CTRL_REG.ISGAIN 	= DRV8711_ISGAIN_40;
	G_CTRL_REG.EXSTALL 	= 0x00;
	G_CTRL_REG.MODE 	= 0x00;
	G_CTRL_REG.RSTEP 	= 0x00;
	G_CTRL_REG.RDIR 	= 0x00;
	G_CTRL_REG.ENBL 	= 0x01;
	st->drv.CTRL = G_CTRL_REG;
	
	// TORQUE Register
/*
	st->drv.TORQUE_Register.Address = REG_TORQUE;
	st->drv.TORQUE_Register.SIMPLTH = DRV8711_SIMPLTH_50;
	st->drv.TORQUE_Register.TORQUE = 0xBA;
*/
	G_TORQUE_REG.Address = REG_TORQUE;
	G_TORQUE_REG.SIMPLTH = DRV8711_SIMPLTH_50;
	G_TORQUE_REG.TORQUE  = 0xBA;
	st->drv.TORQUE = G_TORQUE_REG;

	// OFF Register
/*
	st->drv.OFF_Register.Address = REG_OFF;
	st->drv.OFF_Register.PWMMODE = 0x00;
	st->drv.OFF_Register.TOFF = 0x30;
*/
	G_OFF_REG.Address 	= REG_OFF;
	G_OFF_REG.PWMMODE 	= 0x00;
	G_OFF_REG.TOFF 		= 0x30;
	st->drv.OFF = G_OFF_REG;

	// BLANK Register
/*
	st->drv.BLANK_Register.Address = REG_BLANK;
	st->drv.BLANK_Register.ABT = 0x01;
	st->drv.BLANK_Register.TBLANK = 0x08;
*/	
	G_BLANK_REG.Address = REG_BLANK;
	G_BLANK_REG.ABT 	= 0x01;
	G_BLANK_REG.TBLANK 	= 0x08;
	st->drv.BLANK = G_BLANK_REG;

	// DECAY Register.
/*
	st->drv.DECAY_Register.Address = REG_DECAY;
	st->drv.DECAY_Register.DECMOD = DRV8711_DECMOD_MIXED;
	st->drv.DECAY_Register.TDECAY = 0x10;
*/
	G_DECAY_REG.Address = REG_DECAY;
	G_DECAY_REG.DECMOD  = DRV8711_DECMOD_MIXED;
	G_DECAY_REG.TDECAY 	= 0x10;
	st->drv.DECAY = G_DECAY_REG;

	// STALL Register
/*
	st->drv.STALL_Register.Address = REG_STALL;
	st->drv.STALL_Register.VDIV = DRV8711_VDIV_4;
	st->drv.STALL_Register.SDCNT = DRV8711_SDCNT_8;
	st->drv.STALL_Register.SDTHR = 0x40;
*/
	G_STALL_REG.Address = REG_STALL;
	G_STALL_REG.VDIV 	= DRV8711_VDIV_4;
	G_STALL_REG.SDCNT 	= DRV8711_SDCNT_8;
	G_STALL_REG.SDTHR 	= 0x40;
	st->drv.STALL = G_STALL_REG;

	// DRIVE Register
/*
	st->drv.DRIVE_Register.Address = REG_DRIVE;
	st->drv.DRIVE_Register.IDRIVEP = DRV8711_IDRIVEP_50;
	st->drv.DRIVE_Register.IDRIVEN = DRV8711_IDRIVEN_100;
	st->drv.DRIVE_Register.TDRIVEN = DRV8711_TDRIVEN_500;
	st->drv.DRIVE_Register.TDRIVEP = DRV8711_TDRIVEP_500;
	st->drv.DRIVE_Register.OCPDEG = DRV8711_OCPDEG_2;
	st->drv.DRIVE_Register.OCPTH = DRV8711_OCPTH_500;
*/
	G_DRIVE_REG.Address = REG_DRIVE;
	G_DRIVE_REG.IDRIVEP = DRV8711_IDRIVEP_50;
	G_DRIVE_REG.IDRIVEN = DRV8711_IDRIVEN_100;
	G_DRIVE_REG.TDRIVEP = DRV8711_TDRIVEP_500;
	G_DRIVE_REG.TDRIVEN = DRV8711_TDRIVEN_500;
	G_DRIVE_REG.OCPDEG 	= DRV8711_OCPDEG_2;
	G_DRIVE_REG.OCPTH 	= DRV8711_OCPTH_500;
	st->drv.DRIVE = G_DRIVE_REG;

	// STATUS Register
/*
	st->drv.STATUS_Register.Address = REG_STATUS;
	st->drv.STATUS_Register.STDLAT =	0x00;
	st->drv.STATUS_Register.STD = 		0x00;
	st->drv.STATUS_Register.UVLO = 		0x00;
	st->drv.STATUS_Register.BPDF =		0x00;
	st->drv.STATUS_Register.APDF = 		0x00;
	st->drv.STATUS_Register.BOCP =		0x00;
	st->drv.STATUS_Register.AOCP = 		0x00;
	st->drv.STATUS_Register.OTS =		0x00;
*/
	G_STATUS_REG.Address = REG_STATUS;
	G_STATUS_REG.STDLAT  = 0x00;
	G_STATUS_REG.STD     = 0x00;
	G_STATUS_REG.UVLO    = 0x00;
	G_STATUS_REG.BPDF    = 0x00;
	G_STATUS_REG.APDF    = 0x00;
	G_STATUS_REG.BOCP    = 0x00;
	G_STATUS_REG.AOCP    = 0x00;
	G_STATUS_REG.OTS     = 0x00;
	st->drv.STATUS = G_STATUS_REG;

	WriteAllRegisters( st );
}

void UpdateDRV8711Registers( Stepper_t *st )
{
	// Write All Registers
    if (G_WRITE_ALL_REG == true)
    {
        WriteAllRegisters( st );
        G_WRITE_ALL_REG = false;
    }

    // Read All Registers
    if (G_READ_ALL_REG == true)
    {
        ReadAllRegisters( st );
        G_READ_ALL_REG = false;
    }

    // Reset FAULTS
    if (G_RESET_FAULTS == true)
    {
        SPI_DRV8711_ReadWrite( st, 0x70, 0x00);
        G_STATUS_REG.STDLAT  = 0x00;
        G_STATUS_REG.STD     = 0x00;
        G_STATUS_REG.UVLO    = 0x00;
        G_STATUS_REG.BPDF    = 0x00;
        G_STATUS_REG.APDF    = 0x00;
        G_STATUS_REG.BOCP    = 0x00;
        G_STATUS_REG.AOCP    = 0x00;
        G_STATUS_REG.OTS     = 0x00;
        st->drv.STATUS = G_STATUS_REG;
        G_RESET_FAULTS = false;
    }

    // Manual SPI Write
    if (G_MANUAL_WRITE == true)
    {
        unsigned char byteHi = REGWRITE | (G_WRITE_ADDR << 4) | (G_WRITE_DATA >> 8);
        unsigned char byteLo = G_WRITE_DATA;
        SPI_DRV8711_ReadWrite( st, byteHi, byteLo);
        G_MANUAL_WRITE = false;
    }

    // Manual SPI Read
    if (G_MANUAL_READ == true)
    {
        unsigned char byte = REGREAD | (G_READ_ADDR << 4);
        G_READ_DATA = SPI_DRV8711_ReadWrite( st, byte, 0x00) & 0x0FFF;
        G_MANUAL_READ = false;
    }
}

void WriteAllRegisters( Stepper_t *st )
{
    unsigned char dataHi = 0x00;
    unsigned char dataLo = 0x00;
	
	G_CTRL_REG = st->drv.CTRL;
    // Write CTRL Register
    dataHi = REGWRITE | (G_CTRL_REG.Address << 4) | (G_CTRL_REG.DTIME << 2) | (G_CTRL_REG.ISGAIN);
    dataLo = (G_CTRL_REG.EXSTALL << 7) | (G_CTRL_REG.MODE << 3) | (G_CTRL_REG.RSTEP << 2) | (G_CTRL_REG.RDIR << 1) | (G_CTRL_REG.ENBL);
    SPI_DRV8711_ReadWrite( st, dataHi, dataLo);

	G_TORQUE_REG = st->drv.TORQUE;
    // Write TORQUE Register
    dataHi = REGWRITE | (G_TORQUE_REG.Address << 4) | (G_TORQUE_REG.SIMPLTH);
    dataLo = G_TORQUE_REG.TORQUE;
    SPI_DRV8711_ReadWrite( st, dataHi, dataLo);

	G_OFF_REG = st->drv.OFF;
    // Write OFF Register
    dataHi = REGWRITE | (G_OFF_REG.Address << 4) | (G_OFF_REG.PWMMODE);
    dataLo = G_OFF_REG.TOFF;
    SPI_DRV8711_ReadWrite( st, dataHi, dataLo);

	G_BLANK_REG = st->drv.BLANK;
    // Write BLANK Register
    dataHi = REGWRITE | (G_BLANK_REG.Address << 4) | (G_BLANK_REG.ABT);
    dataLo = G_BLANK_REG.TBLANK;
    SPI_DRV8711_ReadWrite( st, dataHi, dataLo);

	G_DECAY_REG = st->drv.DECAY;
    // Write DECAY Register
    dataHi = REGWRITE | (G_DECAY_REG.Address << 4) | (G_DECAY_REG.DECMOD);
    dataLo = G_DECAY_REG.TDECAY;
    SPI_DRV8711_ReadWrite( st, dataHi, dataLo);

	G_STALL_REG = st->drv.STALL;
    // Write STALL Register
    dataHi = REGWRITE | (G_STALL_REG.Address << 4) | (G_STALL_REG.VDIV << 2) | (G_STALL_REG.SDCNT);
    dataLo = G_STALL_REG.SDTHR;
    SPI_DRV8711_ReadWrite( st, dataHi, dataLo);

	G_DRIVE_REG = st->drv.DRIVE;
    // Write DRIVE Register
    dataHi = REGWRITE | (G_DRIVE_REG.Address << 4) | (G_DRIVE_REG.IDRIVEP << 2) | (G_DRIVE_REG.IDRIVEN);
    dataLo = (G_DRIVE_REG.TDRIVEP << 6) | (G_DRIVE_REG.TDRIVEN << 4) | (G_DRIVE_REG.OCPDEG << 2) | (G_DRIVE_REG.OCPTH);
    SPI_DRV8711_ReadWrite( st, dataHi, dataLo);

	G_STATUS_REG = st->drv.STATUS;
    // Write STATUS Register
    dataHi = REGWRITE | (G_STATUS_REG.Address << 4);
    dataLo = (G_STATUS_REG.STDLAT << 7) | (G_STATUS_REG.STD << 6) | (G_STATUS_REG.UVLO << 5) | (G_STATUS_REG.BPDF << 4) | (G_STATUS_REG.APDF << 3) | (G_STATUS_REG.BOCP << 2) | (G_STATUS_REG.AOCP << 1) | (G_STATUS_REG.OTS);
    SPI_DRV8711_ReadWrite( st, dataHi, dataLo);
}

void ReadAllRegisters( Stepper_t *st )
{
    unsigned char dataHi = 0x00;
    const unsigned char dataLo = 0x00;
    unsigned int readData = 0x00;

    // Read CTRL Register
    dataHi = REGREAD | (G_CTRL_REG.Address << 4);
    readData = SPI_DRV8711_ReadWrite( st, dataHi, dataLo);
    G_CTRL_REG.DTIME        = ((readData >> 10) & 0x0003);
    G_CTRL_REG.ISGAIN       = ((readData >> 8) & 0x0003);
    G_CTRL_REG.EXSTALL      = ((readData >> 7) & 0x0001);
    G_CTRL_REG.MODE         = ((readData >> 3) & 0x000F);
    G_CTRL_REG.RSTEP        = ((readData >> 2) & 0x0001);
    G_CTRL_REG.RDIR         = ((readData >> 1) & 0x0001);
    G_CTRL_REG.ENBL         = ((readData >> 0) & 0x0001);
	st->drv.CTRL = G_CTRL_REG;

    // Read TORQUE Register
    dataHi = REGREAD | (G_TORQUE_REG.Address << 4);
    readData = SPI_DRV8711_ReadWrite( st, dataHi, dataLo);
    G_TORQUE_REG.SIMPLTH    = ((readData >> 8) & 0x0007);
    G_TORQUE_REG.TORQUE     = ((readData >> 0) & 0x00FF);
	st->drv.TORQUE = G_TORQUE_REG;

    // Read OFF Register
    dataHi = REGREAD | (G_OFF_REG.Address << 4);
    readData = SPI_DRV8711_ReadWrite( st, dataHi, dataLo);
    G_OFF_REG.PWMMODE       = ((readData >> 8) & 0x0001);
    G_OFF_REG.TOFF          = ((readData >> 0) & 0x00FF);
	st->drv.OFF = G_OFF_REG;

    // Read BLANK Register
    dataHi = REGREAD | (G_BLANK_REG.Address << 4);
    readData = SPI_DRV8711_ReadWrite( st, dataHi, dataLo);
    G_BLANK_REG.ABT         = ((readData >> 8) & 0x0001);
    G_BLANK_REG.TBLANK      = ((readData >> 0) & 0x00FF);
	st->drv.BLANK = G_BLANK_REG;

    // Read DECAY Register
    dataHi = REGREAD | (G_DECAY_REG.Address << 4);
    readData = SPI_DRV8711_ReadWrite( st, dataHi, dataLo);
    G_DECAY_REG.DECMOD      = ((readData >> 8) & 0x0007);
    G_DECAY_REG.TDECAY      = ((readData >> 0) & 0x00FF);
	st->drv.DECAY = G_DECAY_REG;

    // Read STALL Register
    dataHi = REGREAD | (G_STALL_REG.Address << 4);
    readData = SPI_DRV8711_ReadWrite( st, dataHi, dataLo);
    G_STALL_REG.VDIV        = ((readData >> 10) & 0x0003);
    G_STALL_REG.SDCNT       = ((readData >> 8) & 0x0003);
    G_STALL_REG.SDTHR       = ((readData >> 0) & 0x00FF);
	st->drv.STALL = G_STALL_REG;

    // Read DRIVE Register
    dataHi = REGREAD | (G_DRIVE_REG.Address << 4);
    readData = SPI_DRV8711_ReadWrite( st, dataHi, dataLo);
    G_DRIVE_REG.IDRIVEP     = ((readData >> 10) & 0x0003);
    G_DRIVE_REG.IDRIVEN     = ((readData >> 8) & 0x0003);
    G_DRIVE_REG.TDRIVEP     = ((readData >> 6) & 0x0003);
    G_DRIVE_REG.TDRIVEN     = ((readData >> 4) & 0x0003);
    G_DRIVE_REG.OCPDEG      = ((readData >> 2) & 0x0003);
    G_DRIVE_REG.OCPTH       = ((readData >> 0) & 0x0003);
	st->drv.DRIVE = G_DRIVE_REG;

    // Read STATUS Register
    dataHi = REGREAD | (G_STATUS_REG.Address << 4);
    readData = SPI_DRV8711_ReadWrite( st, dataHi, dataLo);
    G_STATUS_REG.STDLAT     = ((readData >> 7) & 0x0001);
    G_STATUS_REG.STD        = ((readData >> 6) & 0x0001);
    G_STATUS_REG.UVLO       = ((readData >> 5) & 0x0001);
    G_STATUS_REG.BPDF       = ((readData >> 4) & 0x0001);
    G_STATUS_REG.APDF       = ((readData >> 3) & 0x0001);
    G_STATUS_REG.BOCP       = ((readData >> 2) & 0x0001);
    G_STATUS_REG.AOCP       = ((readData >> 1) & 0x0001);
    G_STATUS_REG.OTS        = ((readData >> 0) & 0x0001);
    st->drv.STATUS = G_STATUS_REG;
}

unsigned int SPI_DRV8711_ReadWrite( Stepper_t *st, unsigned char dataHi, unsigned char dataLo)
{
	unsigned int readData = 0;
	
	pin_set( &st->spi_cs );
	readData = spi_rw( dataHi, dataLo );
	pin_reset( &st->spi_cs );

	return readData;
}
