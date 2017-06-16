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

Feb 21, 2012   R. Michaels   port to Intel cpu
                             The board does A16 addressing

---------------------------------------------------------------------------*/


#define NO_REGS			4

/* register offsets */
#define TSETTLE_OFFSET		0x06
#define TSTABLE_OFFSET		0x08
#define DELAY_OFFSET		0x0a
#define PATTERN_OFFSET		0x0c

static unsigned int iRegisterOffsets[NO_REGS] = 
{
	TSETTLE_OFFSET,
	TSTABLE_OFFSET,
	DELAY_OFFSET,
	PATTERN_OFFSET
};

/* register masks */
#define TSETTLE_MASK		0x1f	/* 5 bit register */
#define TSTABLE_MASK		0x1f	/* 5 bit register */
#define DELAY_MASK		0x0f	/* 4 bit register */
#define PATTERN_MASK		0x07	/* 3 bit register */

static unsigned long iRegisterMasks[NO_REGS] = 
{
	TSETTLE_MASK,
	TSTABLE_MASK,
	DELAY_MASK,
	PATTERN_MASK
};

int DEBUG = 1;
int iBoardInitialized = 0;
int iBoardAddress = 0xa00000;
volatile unsigned char *ucRegisterAddresses[NO_REGS];

/*---------------------------- write register --------------------------------*/

int write_HEL(short signal, unsigned short svalue)
{

        unsigned short* pRegAddress;
        long ret;

        if (signal < 0 || signal > 3) {
	  printf("ERROR: write_HEL:  invalid signal %d \n",signal);
          return -1;
	}

        vmeOpenDefaultWindows();
        vmeBusLock();

	ret = vmeBusToLocalAdrs(0x39, (char*)(iBoardAddress + iRegisterOffsets[signal]), (char **)&pRegAddress);

	/* write new output */ 

      	vmeWrite16(pRegAddress,svalue);

	if (DEBUG)
	{
	  printf("drvHEL:write:  signal = %d  svalue = 0x%x  pRegAddress = 0x%x  \n", signal, svalue, pRegAddress);
	}

        vmeBusUnlock();
        vmeCloseDefaultWindows();


	return 0;
}

/*---------------------------- read register --------------------------------*/

unsigned short read_HEL(short signal)
{
 
        unsigned short svalue;
        unsigned short* pRegAddress;
        long ret;

        if (signal < 0 || signal > 3) {
	  printf("ERROR: read_HEL:  invalid signal %d \n",signal);
          return -1;
	}

        vmeOpenDefaultWindows();
        vmeBusLock();

	ret = vmeBusToLocalAdrs(0x39, (char*)(iBoardAddress + iRegisterOffsets[signal]), (char **)&pRegAddress);

	/* read specified register */
	svalue = vmeRead16(pRegAddress);

	if (DEBUG)
	{
	  printf("drvHEL:read: signal = %d; svalue = %d  pRegAddress = 0x%x\n",signal, (int) svalue, pRegAddress);
	}


        vmeBusUnlock();
        vmeCloseDefaultWindows();

	return svalue;

}
