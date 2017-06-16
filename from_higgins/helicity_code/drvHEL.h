/*-------------------------------------------------------*/
/*          Helicity Control Board Device Support
 *
 * Date: June 27, 2002
 * Author: Scott higgins
 *
*/
/*-------------------------------------------------------*/

#ifndef INCdrvHEL
#define INCdrvHEL

extern int init_HEL(int);
extern int write_HEL(short, unsigned long*);
extern int read_HEL(short, unsigned long*);

#endif /* INCdrvHEL */
