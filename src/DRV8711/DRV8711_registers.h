/*******************************************************************************
 *
 *  DRV8711_registers.h - DRV8711 Registers
 *  David Linzberger
 *  DRV8711_FIRMWARE
 *  10/03/2014
 *
 ******************************************************************************/

#ifndef REGISTERS_H_
#define REGISTERS_H_


#define REG_CTRL				0x00
#define REG_TORQUE				0x01
#define REG_OFF					0x02
#define REG_BLANK				0x03
#define REG_DECAY				0x04
#define REG_STALL				0x05
#define REG_DRIVE				0x06
#define REG_STATUS				0x07

#define DRV8711_ISGAIN_5		0x00
#define DRV8711_ISGAIN_10		0x01
#define DRV8711_ISGAIN_20		0x02
#define DRV8711_ISGAIN_40		0x03
#define DRV8711_DTIME_400		0x00
#define DRV8711_DTIME_450		0x01
#define DRV8711_DTIME_650		0x02
#define DRV8711_DTIME_850		0x03
#define DRV8711_SIMPLTH_50		0x00
#define DRV8711_SIMPLTH_100		0x01
#define DRV8711_SIMPLTH_200		0x02
#define DRV8711_SIMPLTH_300		0x03
#define DRV8711_SIMPLTH_400		0x04
#define DRV8711_SIMPLTH_600		0x05
#define DRV8711_SIMPLTH_800		0x06
#define DRV8711_SIMPLTH_1000	0x07
#define DRV8711_DECMOD_FORCE_SLOW		0x00
#define DRV8711_DECMOD_SLOW_MIXED		0x01
#define DRV8711_DECMOD_FORCE_FAST		0x02
#define DRV8711_DECMOD_MIXED			0x03
#define DRV8711_DECMOD_SLOW_AUTO_MIXED 	0x04
#define DRV8711_DECMOD_AUTO_MIXED		0x05
#define DRV8711_SDCNT_0			0x00
#define DRV8711_SDCNT_2			0x01
#define DRV8711_SDCNT_4			0x02
#define DRV8711_SDCNT_8			0x03
#define DRV8711_VDIV_32			0x00
#define DRV8711_VDIV_16			0x01
#define DRV8711_VDIV_8			0x02
#define DRV8711_VDIV_4			0x03
#define DRV8711_OCPTH_250		0x00
#define DRV8711_OCPTH_500		0x01
#define DRV8711_OCPTH_750		0x02
#define DRV8711_OCPTH_1000		0x03
#define DRV8711_OCPDEG_1		0x00
#define DRV8711_OCPDEG_2		0x01
#define DRV8711_OCPDEG_4		0x02
#define DRV8711_OCPDEG_8		0x03
#define DRV8711_TDRIVEN_250		0x00
#define DRV8711_TDRIVEN_500		0x01
#define DRV8711_TDRIVEN_1000	0x02
#define DRV8711_TDRIVEN_2000	0x03
#define DRV8711_TDRIVEP_250		0x00
#define DRV8711_TDRIVEP_500		0x01
#define DRV8711_TDRIVEP_1000	0x02
#define DRV8711_TDRIVEP_2000	0x03
#define DRV8711_IDRIVEN_100		0x00
#define DRV8711_IDRIVEN_200		0x01
#define DRV8711_IDRIVEN_300		0x02
#define DRV8711_IDRIVEN_400		0x03
#define DRV8711_IDRIVEP_50		0x00
#define DRV8711_IDRIVEP_100		0x01
#define DRV8711_IDRIVEP_150		0x02
#define DRV8711_IDRIVEP_200		0x03

// CTRL Register
struct CTRL_Register
{
	unsigned int Address;	// bits 14-12
	unsigned int DTIME;		// bits 11-10
	unsigned int ISGAIN;	// bits 9-8
	unsigned int EXSTALL;	// bit 7
	unsigned int MODE;		// bits 6-3
	unsigned int RSTEP;		// bit 2
	unsigned int RDIR;		// bit 1
	unsigned int ENBL;		// bit 0
};

// TORQUE Register
struct TORQUE_Register
{
	unsigned int Address;	// bits 14-12
	/* Reserved */ 			// bit 11
	unsigned int SIMPLTH;  	// bits 10-8
	unsigned int TORQUE;	// bits 7-0
};

// OFF Register
struct OFF_Register
{
	unsigned int Address;	// bits 14-12
	/* Reserved */ 			// bits 11-9
	unsigned int PWMMODE;  	// bit 8
	unsigned int TOFF;		// bits 7-0
};

// BLANK Register
struct BLANK_Register
{
	unsigned int Address;	// bits 14-12
	/* Reserved */ 			// bits 11-9
	unsigned int ABT;  		// bit 8
	unsigned int TBLANK;	// bits 7-0
};

// DECAY Register
struct DECAY_Register
{
	unsigned int Address;	// bits 14-12
	/* Reserved */ 			// bit 11
	unsigned int DECMOD;  	// bits 10-8
	unsigned int TDECAY;	// bits 7-0
};

// STALL Register
struct STALL_Register
{
	unsigned int Address;	// bits 14-12
	unsigned int VDIV;  	// bits 11-10
	unsigned int SDCNT;		// bits 9-8
	unsigned int SDTHR;		// bits 7-0
};

// DRIVE Register
struct DRIVE_Register
{
	unsigned int Address;	// bits 14-12
	unsigned int IDRIVEP;  	// bits 11-10
	unsigned int IDRIVEN;	// bits 9-8
	unsigned int TDRIVEP;	// bits 7-6
	unsigned int TDRIVEN;	// bits 5-4
	unsigned int OCPDEG;	// bits 3-2
	unsigned int OCPTH;		// bits 1-0
};

// STATUS Register
struct STATUS_Register
{
	unsigned int Address;	// bits 14-12
	/* Reserved */			// bits 11-8
	unsigned int STDLAT;  	// bit 7
	unsigned int STD;		// bit 6
	unsigned int UVLO;		// bit 5
	unsigned int BPDF;		// bit 4
	unsigned int APDF;		// bit 3
	unsigned int BOCP;		// bit 2
	unsigned int AOCP;		// bit 1
	unsigned int OTS;		// bit 0
};

typedef struct drv8711_s
{
	struct CTRL_Register CTRL;
	struct TORQUE_Register TORQUE;
	struct OFF_Register OFF;
	struct BLANK_Register BLANK;
	struct DECAY_Register DECAY;
	struct STALL_Register STALL;
	struct DRIVE_Register DRIVE;
	struct STATUS_Register STATUS;
} drv8711_t;

#endif /* REGISTERS_H_ */
