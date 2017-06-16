/*-------------------------------------------------------*/
/*          Helicity Control Board Device Support
 *
 * Functions: Li Device Support For the Jefferson Lab
 *            Designed Helicity Control Board
 *
 * Date: June 26, 2002
 * Author: Scott higgins
 *
 */
/*-------------------------------------------------------*/

#include        <vxWorks.h>
#include        <types.h>
#include        <stdioLib.h>
#include        <memLib.h>
#include        <string.h>

#include        <alarm.h>
#include        <cvtTable.h>
#include        <dbDefs.h>
#include        <dbAccess.h>
#include        <recSup.h>
#include        <devSup.h>
#include        <devLib.h>
#include        <link.h>
#include        <module_types.h>
#include        <longinRecord.h>

#include        <dbScan.h>
#include        <vxLib.h>
#include        <vme.h>

#include	"devHEL.h"
#include	"drvHEL.h"

/* Create the dset for devLiHEL */
static long init_record();
static long read_longin();

struct {
	long		number;
	DEVSUPFUN	report;
	DEVSUPFUN	init;
	DEVSUPFUN	init_record;
	DEVSUPFUN	get_ioint_info;
	DEVSUPFUN	read_longin;
	DEVSUPFUN	special_linconv;
} devLiHEL = {
	6,
	NULL,
	NULL,
	init_record,
	NULL,
	read_longin,
	NULL
};

/*----------------------------- Init Record -----------------------------------*/
/* Driver Initialization Called from Applications Startup File */

static long init_record(plongin)
struct longinRecord* plongin;
{
	struct vmeio* pvmeio;

	/* Check if Driver has Been Initialized */
	if (!iBoardInitialized)
	{
		recGblRecordError(S_dev_noDevice, (void*)plongin, "devLiHEL:init_record: Driver BAD");
		plongin->pact = TRUE;
		return (S_dev_noDevice);
	}

	/* li.inp must be VME_IO */
	switch (plongin->inp.type)
	{
		case VME_IO:
			break;

		default:
			recGblRecordError(S_db_badField, (void*)plongin, "devLiHEL:init_record: Illegal INP field");
			return (S_db_badField);
	}

	pvmeio = (struct vmeio*)&(plongin->inp.value);

	/* Check Signal Number Validity */
	if ((pvmeio->signal > MAX_LI_SIGNAL_NUM) || (pvmeio->signal < 0))
	{
		recGblRecordError(S_db_badField, (void*)plongin, "devLiHEL:init_record: Illegal INP field (Bad Signal #)");
		return (S_db_badField);
	}
	
	plongin->udf = FALSE;

	return 0;
}

/*----------------------------- Read Li -----------------------------------*/

static long read_longin(plongin)
struct longinRecord* plongin;
{
	struct vmeio* pvmeio;
	int status;
	unsigned long value;

	pvmeio = (struct vmeio*)&(plongin->inp.value);

	if (DEBUG)
		printf("devLiHEL:read_longin: signal is %d\n", pvmeio->signal);

	status = read_HEL(pvmeio->signal, &value);

	if (DEBUG)
		printf("devLiHEL:read_longin: status is %d\n", status);

	if (status == OK)
		plongin->val = value;
	else
		recGblSetSevr(plongin, READ_ALARM, INVALID_ALARM);

	return status;
}
