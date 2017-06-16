/***********************************************************
*
* Code to write/read to helicity board on the Linux VME frontend
* to a default setting that I like. 
*    tsettle=9 --> 100 usec
*    tstable=24 --> 8.6 msec
* and Octet pattern.
*
*/

#define TSETTLE   0
#define TSTABLE   1
#define DELAY     2
#define PATTERN   3

#define default_tsettle 25 
#define default_tstable 27
#define default_pattern 2


#include <string.h>

int main(int argc, char *argv[]) {

  int debug = 0;

  unsigned long rval;

  long myvalue;

  int quantity;

  rval = 0;

  quantity = TSETTLE;
  myvalue = default_tsettle;

  WriteHelBoard(quantity,myvalue);


  quantity = TSTABLE;
  myvalue = default_tstable;

  WriteHelBoard(quantity,myvalue);


  quantity = PATTERN;
  myvalue = default_pattern;

  WriteHelBoard(quantity,myvalue);



  exit(0);

}






