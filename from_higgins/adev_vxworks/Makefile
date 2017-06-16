    INCFLAGS =
VXDIR=/site/vxworks/5.5/ppc/target/h
#    VXDIR=/adaqfs/halla/a-onl/scaler/tornado
    CCPPCFLAGS =  -I$(VXDIR) -DCPU_FAMILY=PPC -DCPU=PPC604 -mlongcall


all: drvHEL.o setupHel.o

drvHEL.o: drvHEL.c  
	rm -f $@
	ccppc -c $(CCPPCFLAGS) drvHEL.c 


setupHel.o: setupHel.c
	rm -f $@
	ccppc -c $(CCPPCFLAGS) setupHel.c

