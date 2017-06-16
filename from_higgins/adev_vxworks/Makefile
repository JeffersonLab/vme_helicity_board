#  Build system

VXWORKS = /site/vxworks
EPICS = /site/epics/R3.13.4/base

# Define host operating system
ifndef OSNAME
  OSNAME := $(subst -,_,$(shell uname))
endif

# Define target architecture
ifndef ARCH
  ARCH = VXWORKSPPC55
endif


ifeq ($(OSNAME),Linux)

  CODA_LIBDIR = $(CODA)/$(ARCH)/lib
  CODA_INCDIR = $(CODA)/extensions/universeDma

  # Potentially unsafe CFLAGS
  CFLAGS = -Wno-unused -DMV5100

  # VxWorks 5.5 for PPC
  ifeq ($(ARCH),VXWORKSPPC55)

    VXVERSION = 5.5
    BINDIR = $(VXWORKS)/$(VXVERSION)/ppc/host/x86-linux/bin
    INCDIR = $(VXWORKS)/$(VXVERSION)/ppc/target/h
    CC = $(BINDIR)/ccppc

    DEFS = -DCPU=PPC604 -DVXWORKS -D_GNU_TOOL -DVXWORKSPPC
    INCS = -I. -I$(INCDIR) -I$(CODA_INCDIR) -I$(EPICS)/include

    CFLAGS += -mcpu=604 -Wall -fno-for-scope -fno-builtin -fvolatile -fstrength-reduce -mlongcall

  endif

  CFLAGS += -O $(DEFS) $(INCS)

endif


# Build rules
.c.o:
	rm -f $@
	$(CC) -c $(CFLAGS) $(INCS) $< -o $@

# Build targets
all: drvHEL.o setupHel.o

