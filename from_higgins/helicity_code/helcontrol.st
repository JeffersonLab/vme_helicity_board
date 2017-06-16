/*-------------------------------------------------------------
		Helicity Board Controls 

Date:		October 7, 2009
Author:		Scott Higgins

Date:		22 July 2010
Author:		G. Croke
Details:	Reworked to use records instead of direct hardware read/write from sequencer.
		Sequencer now only updates readbacks periodically

Date:		21 September 2010
Author:		G. Croke
Details:	Updated for QWeak. Two new patterns, and new TStable timing values.

-------------------------------------------------------------*/

program helicity_control_sequencer

#define HZ_30		0
#define HZ_120		1
#define HZ_240		2

/* initialized flag set in driver */
%%extern int iBoardInitialized;

/* readbacks */
/* tsettle readback from hardware */
int iTSettleReadback;
assign iTSettleReadback to "HELTSETTLEin";
monitor iTSettleReadback;

/* tsettle readback eu value */
double fTSettleReadbackVal;
assign fTSettleReadbackVal to "HELTSETTLEd";

/* tstable readback from hardware */
int iTStableReadback;
assign iTStableReadback to "HELTSTABLEin";
monitor iTStableReadback;

/* tstable readback eu value */
double fTStableReadbackVal;
assign fTStableReadbackVal to "HELTSTABLEd";

/* frequency readback */
double fFreqReadback;
assign fFreqReadback to "HELFREQ";

/* clock readback */
int iClockReadback;
assign iClockReadback to "HELCLOCKd";
monitor iClockReadback;

%{
/* timing values */
double fTSettleVals[32] = {
	10, 20, 30, 40, 50, 60, 70, 80,
	90, 100, 110, 120, 130, 140, 150, 160,
	170, 180, 190, 200, 250, 300, 350, 400,
	450, 500, 550, 600, 700, 800, 900, 1000
};

double fTStableVals[32] = {
	400, 500, 600, 700, 800, 900, 972, 1000,
	1002, 1319, 1349, 1500, 2000, 2500, 3000, 3500,
	4067, 4500, 5000, 7500, 8230, 8500, 9000, 33230,
	33330, 50000, 75000, 100000, 250000, 500000, 750000, 1000000
};
}%

/*------------------------ helicity sequencer ------------------------*/

ss HELICITY_BOARD_STATE_MACHINE
{
	/* uninitialized state */
	state HELICITY_BOARD_OFF
	{
		/* check board initialized */
		when (iBoardInitialized)
		{
		} state HELICITY_BOARD_MAIN_LOOP
	}

	/* main control loop */
	state HELICITY_BOARD_MAIN_LOOP
	{
		/* get readbacks every second */
		when (delay(1.0))
		{
%{
			/* get tsettle time */
			fTSettleReadbackVal = fTSettleVals[iTSettleReadback];

			/* get tstable time and frequency */
			switch (iClockReadback)
			{
				case HZ_30:
					fFreqReadback = 30.0;
					fTStableReadbackVal = ((1.0 / fFreqReadback) * 1000000.0) - fTSettleReadbackVal;
					break;

				case HZ_120:
					fFreqReadback = 120.0;
					fTStableReadbackVal = ((1.0 / fFreqReadback) * 1000000.0) - fTSettleReadbackVal;
					break;

				case HZ_240:
					fFreqReadback = 240.0;
					fTStableReadbackVal = ((1.0 / fFreqReadback) * 1000000.0) - fTSettleReadbackVal;
					break;

				default:	/* free clock */
					fTStableReadbackVal = fTStableVals[iTStableReadback];
					fFreqReadback = (1.0 / (fTSettleReadbackVal + fTStableReadbackVal)) * 1000000.0;
					break;
			}
}%
			/* update records */
			pvPut(fTSettleReadbackVal);
			pvPut(fTStableReadbackVal);
			pvPut(fFreqReadback);

		} state HELICITY_BOARD_MAIN_LOOP
	}
}
