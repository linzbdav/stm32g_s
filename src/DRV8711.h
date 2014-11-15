#ifndef _DRV8711_H_
#define _DRV8711_H_

#define REG_CTRL	0x00
#define REG_TORQUE	0x01
#define REG_OFF		0x02
#define REG_BLANK	0x03
#define REG_DECAY	0x04
#define REG_STALL	0x05
#define REG_DRIVE	0x06
#define REG_STATUS	0x07
#define IS_DRV8711_REG(REG)\
					  (((REG) == REG_CTRL) || \
					  ((REG) == REG_TORQUE) || \
					  ((REG) == REG_OFF) || \
					  ((REG) == REG_BLANK) || \
					  ((REG) == REG_DECAY) || \
					  ((REG) == REG_STALL) || \
					  ((REG) == REG_DRIVE) || \
					  ((REG) == REG_STATUS))

#define DRV8711_ISGAIN_5	0x00
#define DRV8711_ISGAIN_10	0x01
#define DRV8711_ISGAIN_20	0x02
#define DRV8711_ISGAIN_40	0x03
#define IS_DRV8711_ISGAIN(ISGAIN)\
						 (((ISGAIN) == DRV8711_ISGAIN_5) || \
                         ((ISGAIN) == DRV8711_ISGAIN_10) || \
                         ((ISGAIN) == DRV8711_ISGAIN_20) || \
                         ((ISGAIN) == DRV8711_ISGAIN_40))

#define DRV8711_DTIME_400	0x00
#define DRV8711_DTIME_450	0x01
#define DRV8711_DTIME_650	0x02
#define DRV8711_DTIME_850	0x03
#define IS_DRV8711_DTIME(DTIME)\
						 (((DTIME) == DRV8711_DTIME_400) || \
                         ((DTIME) == DRV8711_DTIME_450) || \
                         ((DTIME) == DRV8711_DTIME_650) || \
                         ((DTIME) == DRV8711_DTIME_850))

#define DRV8711_SMPLTH_50	0x00
#define DRV8711_SMPLTH_100	0x01
#define DRV8711_SMPLTH_200	0x02
#define DRV8711_SMPLTH_300	0x03
#define DRV8711_SMPLTH_400	0x04
#define DRV8711_SMPLTH_600	0x05
#define DRV8711_SMPLTH_800	0x06
#define DRV8711_SMPLTH_1000	0x07
#define IS_DRV8711_SMPLTH(SMPLTH)\
						 (((SMPLTH) == DRV8711_SMPLTH_50) || \
                         ((SMPLTH) == DRV8711_SMPLTH_100) || \
                         ((SMPLTH) == DRV8711_SMPLTH_200) || \
						 ((SMPLTH) == DRV8711_SMPLTH_300) || \
						 ((SMPLTH) == DRV8711_SMPLTH_400) || \
						 ((SMPLTH) == DRV8711_SMPLTH_600) || \
						 ((SMPLTH) == DRV8711_SMPLTH_800) || \
                         ((SMPLTH) == DRV8711_SMPLTH_1000))

#define DRV8711_DECMOD_FORCE_SLOW	0x00
#define DRV8711_DECMOD_SLOW_MIXED	0x01
#define DRV8711_DECMOD_FORCE_FAST	0x02
#define DRV8711_DECMOD_MIXED		0x03
#define DRV8711_DECMOD_SLOW_AUTO_MIXED 0x04
#define DRV8711_DECMOD_AUTO_MIXED	0x05
#define IS_DRV8711_DECMOD(DECMOD)\
						 (((DECMOD) == DRV8711_DECMOD_FORCE_SLOW) || \
                         ((DECMOD) == DRV8711_DECMOD_SLOW_MIXED) || \
                         ((DECMOD) == DRV8711_DECMOD_FORCE_FAST) || \
						 ((DECMOD) == DRV8711_DECMOD_MIXED) || \
						 ((DECMOD) == DRV8711_DECMOD_SLOW_AUTO_MIXED) || \
                         ((DECMOD) == DRV8711_DECMOD_AUTO_MIXED))

#define DRV8711_SDCNT_0	0x00
#define DRV8711_SDCNT_2	0x01
#define DRV8711_SDCNT_4	0x02
#define DRV8711_SDCNT_8	0x03
#define IS_DRV8711_SDCNT(SDCNT)\
						 (((SDCNT) == DRV8711_SDCNT_0) || \
                         ((SDCNT) == DRV8711_SDCNT_2) || \
                         ((SDCNT) == DRV8711_SDCNT_4) || \
                         ((SDCNT) == DRV8711_SDCNT_8))

#define DRV8711_VDIV_32	0x00
#define DRV8711_VDIV_16	0x01
#define DRV8711_VDIV_8	0x02
#define DRV8711_VDIV_4	0x03
#define IS_DRV8711_VDIV(VDIV)\
						 (((VDIV) == DRV8711_VDIV_32) || \
                         ((VDIV) == DRV8711_VDIV_16) || \
                         ((VDIV) == DRV8711_VDIV_8) || \
                         ((VDIV) == DRV8711_VDIV_4))

#define DRV8711_OCPTH_250	0x00
#define DRV8711_OCPTH_500	0x01
#define DRV8711_OCPTH_750	0x02
#define DRV8711_OCPTH_1000	0x03
#define IS_DRV8711_OCPTH(OCPTH)\
						 (((OCPTH) == DRV8711_OCPTH_250) || \
                         ((OCPTH) == DRV8711_OCPTH_500) || \
                         ((OCPTH) == DRV8711_OCPTH_750) || \
                         ((OCPTH) == DRV8711_OCPTH_1000))

#define DRV8711_OCPDEG_1	0x00
#define DRV8711_OCPDEG_2	0x01
#define DRV8711_OCPDEG_4	0x02
#define DRV8711_OCPDEG_8	0x03
#define IS_DRV8711_OCPDEG(OCPDEG)\
						 (((OCPDEG) == DRV8711_OCPDEG_1) || \
                         ((OCPDEG) == DRV8711_OCPDEG_2) || \
                         ((OCPDEG) == DRV8711_OCPDEG_4) || \
                         ((OCPDEG) == DRV8711_OCPDEG_8))

#define DRV8711_TDRIVEN_250		0x00
#define DRV8711_TDRIVEN_500		0x01
#define DRV8711_TDRIVEN_1000	0x02
#define DRV8711_TDRIVEN_2000	0x03
#define IS_DRV8711_TDRIVEN(TDRIVEN)\
						 (((TDRIVEN) == DRV8711_TDRIVEN_250) || \
                         ((TDRIVEN) == DRV8711_TDRIVEN_500) || \
                         ((TDRIVEN) == DRV8711_TDRIVEN_1000) || \
                         ((TDRIVEN) == DRV8711_TDRIVEN_2000))

#define DRV8711_TDRIVEP_250		0x00
#define DRV8711_TDRIVEP_500		0x01
#define DRV8711_TDRIVEP_1000	0x02
#define DRV8711_TDRIVEP_2000	0x03
#define IS_DRV8711_TDRIVEP(TDRIVEP)\
						 (((TDRIVEP) == DRV8711_TDRIVEP_250) || \
                         ((TDRIVEP) == DRV8711_TDRIVEP_500) || \
                         ((TDRIVEP) == DRV8711_TDRIVEP_1000) || \
                         ((TDRIVEP) == DRV8711_TDRIVEP_2000))

#define DRV8711_IDRIVEN_100	0x00
#define DRV8711_IDRIVEN_200	0x01
#define DRV8711_IDRIVEN_300	0x02
#define DRV8711_IDRIVEN_400	0x03
#define IS_DRV8711_IDRIVEN(IDRIVEN)\
						 (((IDRIVEN) == DRV8711_IDRIVEN_100) || \
                         ((IDRIVEN) == DRV8711_IDRIVEN_200) || \
                         ((IDRIVEN) == DRV8711_IDRIVEN_300) || \
                         ((IDRIVEN) == DRV8711_IDRIVEN_400))

#define DRV8711_IDRIVEP_50	0x00
#define DRV8711_IDRIVEP_100	0x01
#define DRV8711_IDRIVEP_150	0x02
#define DRV8711_IDRIVEP_200	0x03
#define IS_DRV8711_IDRIVEP(IDRIVEP)\
						 (((IDRIVEP) == DRV8711_IDRIVEP_50) || \
                         ((IDRIVEP) == DRV8711_IDRIVEP_100) || \
                         ((IDRIVEP) == DRV8711_IDRIVEP_150) || \
                         ((IDRIVEP) == DRV8711_IDRIVEP_200))


typedef struct
{
	union
	{
		struct {
			uint8_t enbl:1;
			uint8_t rdir:1;
			uint8_t rstep:1;
			uint8_t mode:4;
			uint8_t exstall:1;
			uint8_t isgain:2;
			uint8_t dtime:2;
			uint8_t RESERVED:4;
		};
		uint16_t word;
	};
} DRV8711_REG_CTRL;

typedef struct
{
	union
	{
		struct {
			uint8_t torque:8;
			uint8_t smplth:3;
			uint8_t RESERVED:5;
		};
		uint16_t word;
	};
} DRV8711_REG_TORQUE;

typedef struct
{
	union
	{
		struct {
			uint8_t toff:8;
			uint8_t pwmmode:1;
			uint8_t RESERVED:7;
		};
		uint16_t word;
	};
} DRV8711_REG_OFF;

typedef struct
{
	union
	{
		struct {
			uint8_t tblank:8;
			uint8_t abt:1;
			uint8_t RESERVED:7;
		};
		uint16_t word;
	};
} DRV8711_REG_BLANK;

typedef struct
{
	union
	{
		struct {
			uint8_t tdecay:8;
			uint8_t decmod:3;
			uint8_t RESERVED:5;
		};
		uint16_t word;
	};
} DRV8711_REG_DECAY;

typedef struct
{
	union
	{
		struct {
			uint8_t sdthr:8;
			uint8_t sdcnt:2;
			uint8_t vdiv:2;
			uint8_t RESERVED:4;
		};
		uint16_t word;
	};
} DRV8711_REG_STALL;

typedef struct
{
	union
	{
		struct {
			uint8_t ocpth:2;
			uint8_t ocpdeg:2;
			uint8_t tdriven:2;
			uint8_t tdrivep:2;
			uint8_t idriven:2;
			uint8_t idrivep:2;
			uint8_t RESERVED:4;
		};
		uint16_t word;
	};
} DRV8711_REG_DRIVE;

typedef struct
{
	union
	{
		struct {
			uint8_t ots:1;
			uint8_t aocp:1;
			uint8_t bocp:1;
			uint8_t apdf:1;
			uint8_t bpdf:1;
			uint8_t uvlo:1;
			uint8_t std:1;
			uint8_t stdlat:1;
			uint8_t RESERVED:8;
		};
		uint16_t word;
	};
} DRV8711_REG_STATUS;

typedef struct drv8711Singleton {
    DRV8711_REG_CTRL ctrl;
    DRV8711_REG_TORQUE torque;
    DRV8711_REG_OFF off;
    DRV8711_REG_BLANK blank;
    DRV8711_REG_DECAY decay;
    DRV8711_REG_STALL stall;
    DRV8711_REG_DRIVE drive;
    DRV8711_REG_STATUS status;
} drv8711_t;

#endif // _DRV8711_H_
