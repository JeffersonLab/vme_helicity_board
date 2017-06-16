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


  # VxWorks 5.3 for 68k
  ifeq ($(ARCH),VXWORKS68K51)

    VXVERSION = 5.3
    BINDIR = $(VXWORKS)/$(VXVERSION)/68k/host/x86-linux/bin
    INCDIR = $(VXWORKS)/$(VXVERSION)/68k/target/h
    CC = $(BINDIR)/cc68k

    DEFS = -DCPU=MC68040 -DVXWORKS -DVXWORKS68K51
    INCS = -I. -I$(INCDIR) -I$(CODA_INCDIR)

    CFLAGS += -Wall -mc68020 -fvolatile -fstrength-reduce -nostdinc

  endif

  CFLAGS += -O $(DEFS) $(INCS)

endif


# Build rules
.c.o:
	$(CC) -c $(CFLAGS) $(INCS) $< -o $@


INSTALL_DIR = ~/vme

# Build targets

all: drvHEL.o devLoHEL.o devLiHEL.o

clean:
	@rm -f drvHel/*.0 drvHel/*~

echoarch:
	@echo "Make for $(ARCH)"

