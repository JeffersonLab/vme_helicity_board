/* Set up the helicity board.
Load on VME:
ld</adaqfs/halla/adev/vme/helboard/setupHel.o
---------------------------------------------------------------------------*/

#define ITSETTLE 0
#define ITSTABLE 1
#define IDELAY   2
#define IPATTERN 6

#include        <vxWorks.h>
#include	<types.h>
#include        <vme.h>
#include        <stdioLib.h>

VOID setupHel(unsigned long tsettle, unsigned long tstable, unsigned long delay, unsigned long pattern)  {

  // arguments are indices that correspond to values of tsettle, etc.
  // see the user manual, although the observed values were in some cases
  // different and (importantly) the power-up state is very different from
  // the listed defaults.  The vxWorks boot process must load defaults.

  // examples -- observed on the scope
  // tsettle:
  //     9 = 100 usec (typical default)
  //    19 = 200 usec
  //    23 = 400 usec

  // tstable: 
  //     4 = 800 usec
  //     6 = 1 msec   (my default)
  //    12 = 2 msec
  //    13 = 2.5 msec
  //    16 = 4.05 msec

  // pattern: 
  //     0 = pair
  //     1 = quartet
  //     2 = octet  (my default)
  //     3 = toggle (looks like pair)



int address=0xa00000;

init_HEL(address);

write_HEL(ITSETTLE,&tsettle);
write_HEL(ITSTABLE,&tstable);
write_HEL(IDELAY,&delay);
write_HEL(IPATTERN,&pattern);

read_HEL(ITSETTLE,&tsettle);
read_HEL(ITSTABLE,&tstable);
read_HEL(IDELAY,&delay);
read_HEL(IPATTERN,&pattern);

}

VOID setupHelDef(void)  {
// uses defaults

int address=0xa00000;

unsigned long tsettle = 9;
unsigned long tstable = 6;
unsigned long delay   = 0;
unsigned long pattern = 2;

init_HEL(address);

write_HEL(ITSETTLE,&tsettle);
write_HEL(ITSTABLE,&tstable);
write_HEL(IDELAY,&delay);
write_HEL(IPATTERN,&pattern);

read_HEL(ITSETTLE,&tsettle);
read_HEL(ITSTABLE,&tstable);
read_HEL(IDELAY,&delay);
read_HEL(IPATTERN,&pattern);

}
