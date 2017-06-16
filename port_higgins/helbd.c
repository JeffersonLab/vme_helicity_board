/***********************************************************
*
* Code to write/read to helicity board on the Linux VME frontend
*
*/

#define TSETTLE   0
#define TSTABLE   1
#define DELAY     2
#define PATTERN   3

#include <string.h>

int main(int argc, char *argv[]) {

  int debug = 0;

  unsigned short rval;


  write_HEL(0,15);

  rval = read_HEL(0);

  printf("Value = %d = 0x%x \n",rval,rval,"good bye \n");

  exit(0);

}






