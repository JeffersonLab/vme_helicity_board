/*-------------------------------------------------------*/
/*          Helicity Control Board Device Support
 *
 * Functions: Lo Device Support For the Jefferson Lab
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
#include        <longoutRecord.h>

#include        <dbScan.h>
#include        <vxLib.h>
#include        <vme.h>

#include	"devHEL.h"
#include	"drvHEL.h"

/* Create the dset for devLoHEL */
static long init_record();
static long write_longout();

struct {
	long            number;
	DEVSUPFUN       report;
	DEVSUPFUN       init;
	DEVSUPFUN       init_record;
	DEVSUPFUN       get_ioint_info;
	DEVSUPFUN       write_longout;
	DEVSUPFUN       special_linconv;
} devLoHEL = {
	6,
	NULL,
	NULL,
	init_record,
	NULL,
	write_longout,
	NULL
};

/*----------------------------- Init Record -----------------------------------*/
/* Driver Initialization Called from Applications Startup File */

static long init_record(plongout)
struct longoutRecord* plongout;
{
	struct vmeio* pvmeio;

	/* Check if Driver has Been Initialized */
	if (!iBoardInitialized)
	{
		recGblRecordError(S_dev_noDevice, (void*)plongout, "devLoHEL:init_record: Driver BAD");
		plongout->pact = TRUE;
		return (S_dev_noDevice);
	}

	/* lo.out must be VME_IO */
	switch (plongout->out.type)
	{
		case VME_IO:
			break;
	
		default:
			recGblRecordError(S_db_badField, (void*)plongout, "devLoHEL:init_record: Illegal OUT field");
			return (S_db_badField);
	}

	pvmeio = (struct vmeio*)&(plongout->out.value.vmeio);

	/* Check Signal Number Validity */
	if ((pvmeio->signal > MAX_LO_SIGNAL_NUM) || (pvmeio->signal < 0))
	{
		recGblRecordError(S_db_badField, (void*)plongout, "devLoHEL:init_record: Illegal OUT field (Bad Signal #)");
		return (S_db_badField);
	}

	plongout->udf = FALSE;
	
	return 0;
}

/*---------------------------- Write LongOut -------------------------------*/

static long write_longout(plongout)
struct longoutRecord* plongout;
{
	struct vmeio* pvmeio;
	int status;
	unsigned long value;

	pvmeio = &(plongout->out.value.vmeio);

	value = plongout->val;

	status = write_HEL(pvmeio->signal, &value);

	if (status != OK)
		recGblSetSevr(plongout, WRITE_ALARM, INVALID_ALARM);

	return status;
}
