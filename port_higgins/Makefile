#
# File:
#    Makefile
#
export DEBUG=1
#

HELBDLIB	= drvHEL.so

ifndef LINUXVME_LIB
	LINUXVME_LIB	= ${CODA}/extensions/linuxvme/libs
endif
ifndef LINUXVME_INC
	LINUXVME_INC	= ${CODA}/extensions/linuxvme/include
endif

# libs for the client
LIBS  = ${HELBDLIB} ${LINUXVME_LIB}/libjvme.so


# DEFs for compiling primary readout lists
CC			= gcc
AR                      = ar
RANLIB                  = ranlib
CFLAGS			= -O3 -w -I${LINUXVME_INC} -I. -I/usr/include -I${CODA}/common/include\
			  -L${LINUXVME_LIB} -L. -DJLAB
CFLAGS			+= -ljvme -ltir $(ROLLIBS)
CFLAGS			+= -DLINUX -DDAYTIME=\""`date`"\"
ifdef DEBUG
CFLAGS			+= -Wall -g
endif

# DEFs for compiling CODA readout lists
CCRL			= ${CODA_BIN}/ccrl
CODA_INCS		= -I.  -I${LINUXVME_INC} -I${CODA}/common/include
CODA_LIBDIRS            = -L. -L${LINUXVME_LIB}
CODA_LIBS		= -ljvme -ltir
CODA_DEFS		= -DLINUX -DDAYTIME=\""`date`"\"
CODA_CFLAGS		= -O -w -fpic -shared ${CODA_INCS} ${CODA_LIBDIRS} \
			  ${CODA_LIBS} ${CODA_DEFS}
ifdef DEBUG
CODA_CFLAGS		+= -Wall -g
endif

all: $(HELBDLIB) helbd

drvHEL.so: drvHEL.c 
	@echo
	@echo "Building $@ from $<"
	@echo
	$(CC) -fpic -shared $(CFLAGS) -D_GNU_SOURCE -DINIT_NAME=$(@:.so=__init) -o $@ $<

helbd: helbd.o
	$(CC) -o $@ helbd.c $(LIBS)

clean distclean:
	@rm -f  $(HELBDLIB) *.o *~ 

.PHONY: all
