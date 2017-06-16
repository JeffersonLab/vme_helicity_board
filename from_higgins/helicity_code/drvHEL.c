/*---------------------------------------------------------------------------
		Helicity Control Board Driver Support
            
Date:		June 27, 2002
Author:		Scott Higgins
Functions:	Driver Support For the Helicity Control Board. Initialize, Read, Write. 

Date:		July 27, 2010
Author:		G. Croke
Details:	Updated for new helicity control board, new registers, etc.

Date:		Sept 21, 2010
Author:		G. Croke
Details:	New register settings. QWeak experiment requires two new modes of operation,
		hexo-quad and octo-quad, along with new TStable timing values.

---------------------------------------------------------------------------*/

#include        <vxWorks.h>
#include	<types.h>
#include        <vme.h>
#include        <stdioLib.h>
#include        <drvSup.h>
#include	<dbDefs.h>
#include	<link.h>

#define NO_REGS			8

/* register offsets */
#define TSETTLE_OFFSET		0x07
#define TSTABLE_OFFSET		0x09
#define DELAY_OFFSET		0x0b
#define MONTH_OFFSET		0x00
#define DAY_OFFSET		0x01
#define YEAR_OFFSET		0x02
#define PATTERN_OFFSET		0x0d
#define CLOCK_OFFSET		0x0f

static unsigned int iRegisterOffsets[NO_REGS] = 
{
	TSETTLE_OFFSET,
	TSTABLE_OFFSET,
	DELAY_OFFSET,
	MONTH_OFFSET,
	DAY_OFFSET,
	YEAR_OFFSET,
	PATTERN_OFFSET,
	CLOCK_OFFSET
};

/* register masks */
#define TSETTLE_MASK		0x1f	/* 5 bit register */
#define TSTABLE_MASK		0x1f	/* 5 bit register */
#define DELAY_MASK		0x0f	/* 4 bit register */
#define MONTH_MASK		0xff
#define DAY_MASK		0xff
#define YEAR_MASK		0xff
#define PATTERN_MASK		0x07	/* 3 bit register */
#define CLOCK_MASK		0xff

static unsigned int iRegisterMasks[NO_REGS] = 
{
	TSETTLE_MASK,
	TSTABLE_MASK,
	DELAY_MASK,
	MONTH_MASK,
	DAY_MASK,
	YEAR_MASK,
	PATTERN_MASK,
	CLOCK_MASK
};

int DEBUG = 0;
int iBoardInitialized = 0;
volatile unsigned char *ucRegisterAddresses[NO_REGS];

/*------------------------ initialize board ---------------------------*/

int init_HEL(int iBoardAddress)
{
	char* pRegAddress;
	char c;
	int i, iBoardFound = 0;

	/* get the access address for all registers */
	for (i = 0; i < NO_REGS; i++)
	{
		/* get address of next register, tell card we are using standard supervisory access */
		if (sysBusToLocalAdrs(VME_AM_STD_SUP_DATA, (char*)(iBoardAddress + iRegisterOffsets[i]), &pRegAddress) != OK)
		{
			printf("\n...addressing error in HEL driver register #%d...\n\n", i);
			iBoardInitialized = 0;
			return ERROR;
		}

		/* add this next address to register map */
		ucRegisterAddresses[i] = pRegAddress;

		/* test this location */
		if (vxMemProbe(ucRegisterAddresses[i], VX_READ, 1, &c) == OK )
		{
			if (!iBoardFound) /* If card had not been previously detected */
				printf("\n...helicity control board located...\n\n", i);

			iBoardFound = 1;
		}
		else
		{
			printf("\n...helicity control reg#%d not responding...\n\n", i);
			iBoardInitialized = 0;
			return ERROR;
		}
	}

	/* all done okay */
	printf("\n...helicity control board initialized...\n\n", i);
	iBoardInitialized = 1;

	return OK;
}

/*---------------------------- write register --------------------------------*/

int write_HEL(short signal, unsigned long *pValue)
{
	/* write new output */
	*ucRegisterAddresses[signal] = (char)(*pValue & iRegisterMasks[signal]);

	if (DEBUG)
	{
		printf("drvHEL:write_HEL: signal = %d; (*pValue) = %ld; (*ucRegisterAddresses[%d]) = %d; ucRegisterAddresses[%d] = %p\n", 
			signal, *pValue, signal, *ucRegisterAddresses[signal], signal, ucRegisterAddresses[signal]);
	}

	return OK;
}

/*---------------------------- read register --------------------------------*/

int read_HEL(short signal, unsigned long *pValue)
{
	/* read specified register */
	*pValue = (unsigned long)(*ucRegisterAddresses[signal] & iRegisterMasks[signal]);

	if (DEBUG)
	{
		printf("drvHEL:read_HEL: signal = %d; (*pValue) = %ld; (*ucRegisterAddresses[%d]) = %d; ucRegisterAddresses[%d] = %p\n", 
			signal, *pValue, signal, *ucRegisterAddresses[signal], signal, ucRegisterAddresses[signal]);
	}

	return OK;
}
