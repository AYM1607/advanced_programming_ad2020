# Generated automatically from Makefile.in by configure.
#-----------------------------------------------------------------------------
#
# Makefile for the platform macosx10.16, on the host marianos-macbook-pro.local.
#
#-----------------------------------------------------------------------------

CC=gcc
DEFS=-DHAVE_CONFIG_H -DMACOSX=11600
CFLAGS=-D_REENTRANT -O2 -Weverything -Wno-unknown-warning-option -Wno-disabled-macro-expansion -Wno-missing-variable-declarations -Wno-date-time -Wno-format-y2k
# CC=gcc
# CFLAGS=-O2 -W -Wall -Wimplicit -Wstrict-prototypes -Wmissing-prototypes
prefix=/usr/local
TOPDIR=/Users/marianouvalle/dev/school/advanced_programming_ad2020/libncftp-3.2.6
CPPFLAGS=-I. -I$(TOPDIR)/libncftp -I$(TOPDIR)/sio -I$(TOPDIR)/Strn

SYSLIBS=
LIBS=-lncftp -lsio -lStrn $(SYSLIBS)
STRIPFLAG=-Wl,-x
LDFLAGS=-L$(TOPDIR)/libncftp -L$(TOPDIR)/sio -L$(TOPDIR)/Strn

DELETE=/bin/rm -rf
LIST=/bin/ls -l
EXEEXT=
OBJEXT=o

PROGS=simpleget$(EXEEXT)

all: $(PROGS)

install: $(PROGS)

simpleget$(EXEEXT): simpleget.c $(TOPDIR)/libncftp/ncftp.h $(TOPDIR)/libncftp/ncftp_errno.h $(TOPDIR)/libncftp/libncftp.a simpleget.c
	@/Users/marianouvalle/dev/school/advanced_programming_ad2020/libncftp-3.2.6/libncftp/ccdv $(CC) $(CFLAGS) $(DEFS) $(CPPFLAGS) simpleget.c -o simpleget$(EXEEXT) $(LDFLAGS) $(LIBS) $(STRIPFLAG)
	-@$(LIST) $(PROGS)

$(TOPDIR)/libncftp/libncftp.a:
	[ -f $(TOPDIR)/libncftp/libncftp.a ]

clean:
	-$(DELETE) $(PROGS)
	-$(DELETE) *.$(OBJEXT)
	-$(DELETE) *.dSYM
	-$(DELETE) core csetc.pch SunWS_cache
