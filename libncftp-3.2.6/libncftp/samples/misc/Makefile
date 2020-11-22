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
LIBS_MIN=-lncftp -lStrn $(SYSLIBS)
STRIPFLAG=-Wl,-x
LDFLAGS=-L$(TOPDIR)/libncftp -L$(TOPDIR)/sio -L$(TOPDIR)/Strn

DELETE=/bin/rm -rf
LIST=/bin/ls -l
EXEEXT=
OBJEXT=o

PROGS=codepw$(EXEEXT) getwelcome$(EXEEXT) ncftpgetbytes$(EXEEXT) ncftpgettomem$(EXEEXT) pncftp$(EXEEXT) unlstest$(EXEEXT)

all: $(PROGS)
	-@$(LIST) $(PROGS)

install: $(PROGS)

codepw$(EXEEXT): codepw.c $(TOPDIR)/libncftp/ncftp.h $(TOPDIR)/libncftp/ncftp_errno.h $(TOPDIR)/libncftp/libncftp.a
	@/Users/marianouvalle/dev/school/advanced_programming_ad2020/libncftp-3.2.6/libncftp/ccdv $(CC) $(CFLAGS) $(DEFS) $(CPPFLAGS) codepw.c -o codepw$(EXEEXT) $(LDFLAGS) $(LIBS_MIN) $(STRIPFLAG)

getwelcome$(EXEEXT): getwelcome.c $(TOPDIR)/libncftp/ncftp.h $(TOPDIR)/libncftp/ncftp_errno.h $(TOPDIR)/libncftp/libncftp.a
	@/Users/marianouvalle/dev/school/advanced_programming_ad2020/libncftp-3.2.6/libncftp/ccdv $(CC) $(CFLAGS) $(DEFS) $(CPPFLAGS) getwelcome.c -o getwelcome$(EXEEXT) $(LDFLAGS) $(LIBS) $(STRIPFLAG)

ncftpgetbytes$(EXEEXT): ncftpgetbytes.c $(TOPDIR)/libncftp/ncftp.h $(TOPDIR)/libncftp/ncftp_errno.h $(TOPDIR)/libncftp/libncftp.a
	@/Users/marianouvalle/dev/school/advanced_programming_ad2020/libncftp-3.2.6/libncftp/ccdv $(CC) $(CFLAGS) $(DEFS) $(CPPFLAGS) ncftpgetbytes.c -o ncftpgetbytes$(EXEEXT) $(LDFLAGS) $(LIBS) $(STRIPFLAG)

ncftpgettomem$(EXEEXT): ncftpgettomem.c $(TOPDIR)/libncftp/ncftp.h $(TOPDIR)/libncftp/ncftp_errno.h $(TOPDIR)/libncftp/libncftp.a
	@/Users/marianouvalle/dev/school/advanced_programming_ad2020/libncftp-3.2.6/libncftp/ccdv $(CC) $(CFLAGS) $(DEFS) $(CPPFLAGS) ncftpgettomem.c -o ncftpgettomem$(EXEEXT) $(LDFLAGS) $(LIBS) $(STRIPFLAG)

pncftp$(EXEEXT): pncftp.c $(TOPDIR)/libncftp/ncftp.h $(TOPDIR)/libncftp/ncftp_errno.h $(TOPDIR)/libncftp/libncftp.a
	@/Users/marianouvalle/dev/school/advanced_programming_ad2020/libncftp-3.2.6/libncftp/ccdv $(CC) $(CFLAGS) $(DEFS) $(CPPFLAGS) pncftp.c -o pncftp$(EXEEXT) $(LDFLAGS) $(LIBS) $(STRIPFLAG)

unlstest$(EXEEXT): unlstest.c $(TOPDIR)/libncftp/ncftp.h $(TOPDIR)/libncftp/ncftp_errno.h $(TOPDIR)/libncftp/libncftp.a
	@/Users/marianouvalle/dev/school/advanced_programming_ad2020/libncftp-3.2.6/libncftp/ccdv $(CC) $(CFLAGS) $(DEFS) $(CPPFLAGS) unlstest.c -o unlstest$(EXEEXT) $(LDFLAGS) $(LIBS) $(STRIPFLAG)

$(TOPDIR)/libncftp/libncftp.a:
	[ -f $(TOPDIR)/libncftp/libncftp.a ]

clean:
	-$(DELETE) $(PROGS)
	-$(DELETE) *.$(OBJEXT)
	-$(DELETE) *.dSYM
	-$(DELETE) core csetc.pch SunWS_cache
