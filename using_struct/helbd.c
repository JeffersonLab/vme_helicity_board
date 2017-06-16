/***********************************************************
*
* Code to write/read to helicity board on the Linux VME frontend
*
* Note, to get PATTERN=octet use myvalue=2
*  for a TSETTLE of 50usec, use myvalue=4, etc
*  TSTABLE
*    24      8.6 msec
*    27      33.5 msec
*/

#define TSETTLE   0
#define TSTABLE   1
#define DELAY     2
#define PATTERN   3

#include <string.h>

int main(int argc, char *argv[]) {

  int debug = 0;

  unsigned long rval;

  long myvalue;

  int quantity = TSTABLE;

  myvalue = 27;   
  rval = 0;

  printf("myvalue = 0x%x \n",myvalue); 

  // Better to process args .... do it that way later

  printf("****** Write a value to the board \n");

  WriteHelBoard(quantity,myvalue);

  printf("****** read again \n");

  rval = ReadHelBoard(quantity);

  printf("Return value %d = 0x%x \n",rval,rval);

  printf("good bye \n");

  exit(0);

}






