# Generated automatically from Makefile.in by configure.
#-----------------------------------------------------------------------------
#
# SocketIO makefile for the platform macosx10.16, on the host marianos-macbook-pro.local.
#
#-----------------------------------------------------------------------------
VER=6.3
CC=gcc
CFLAGS=-D_REENTRANT -O2 -Weverything -Wno-unknown-warning-option -Wno-disabled-macro-expansion -Wno-missing-variable-declarations -Wno-date-time -Wno-format-y2k
#CFLAGS=-O2 -g -W -Wall -Wimplicit -Wstrict-prototypes -Wmissing-prototypes
CPPFLAGS=-I. -I$(TOPDIR)/libncftp -I$(TOPDIR)/sio -I$(TOPDIR)/Strn
LDFLAGS=-L$(TOPDIR)/libncftp -L$(TOPDIR)/sio -L$(TOPDIR)/Strn
SOCKS_LIBS=
LIBS= $(SOCKS_LIBS)
DEFS=-DHAVE_CONFIG_H -DMACOSX=11600
PREFIX=/usr/local
LIB=libsio.a
LIB_d=libsio_d.a
LIBSO=libsio.so.5
LIBSOS=libsio.so
STRIP=strip
MAKE=
CCDV=@/Users/marianouvalle/dev/school/advanced_programming_ad2020/libncftp-3.2.6/libncftp/ccdv 

DELETE=/bin/rm -rf
COPY=/bin/cp -pr
LIST=/bin/ls -l
MKDIR=mkdir -m 755 -p
SYMLINK=/bin/ln -s
HARDLINK=/bin/ln

OBJS_U=\
	UAccept.o  UBind.o	UConnectByName.o  UConnect.o \
	UNew.o	   URecvfrom.o	USendtoByName.o   USendto.o

OBJS=$(OBJS_U) \
	DNSUtil.o   main.o	 PRead.o   PWrite.o \
	SAccept.o   SBind.o	 SClose.o  SConnectByName.o \
	SConnect.o  SError.o	 SNew.o    SocketUtil.o \
	SRead.o     SReadline.o  SRecv.o   SRecvfrom.o \
	SRecvmsg.o  SSelect.o	 SSend.o   SSendtoByName.o \
	SSendto.o   StrAddr.o	 SWait.o   SWrite.o

SOBJS_U=\
	UAccept.so  UBind.so	UConnectByName.so  UConnect.so \
	UNew.so	   URecvfrom.so	USendtoByName.so   USendto.so

SOBJS=$(SOBJS_U) \
	DNSUtil.so   main.so	 PRead.so   PWrite.so \
	SAccept.so   SBind.so	 SClose.so  SConnectByName.so \
	SConnect.so  SError.so	 SNew.so    SocketUtil.so \
	SRead.so     SReadline.so  SRecv.so   SRecvfrom.so \
	SRecvmsg.so  SSelect.so	 SSend.so   SSendtoByName.so \
	SSendto.so   StrAddr.so	 SWait.so   SWrite.so

all: $(LIB)
	-@echo 'Done.'

$(LIB): $(OBJS)
	-@$(DELETE) $(LIB)
	@/Users/marianouvalle/dev/school/advanced_programming_ad2020/libncftp-3.2.6/libncftp/ccdv ar r $(LIB) $(OBJS)
	-ranlib $(LIB)
	-@echo $(VER) > sio.version
	-@chmod a+r $(LIB) sio.h usio.h
	-@if [ "x@DEBUGBUILD@" = xyes ] ; then $(COPY) "$(LIB)" "$(LIB_d)" ; fi
	-@$(LIST) "$(LIB)" "$(LIB_d)" 2>/dev/null

install: $(LIB)
	$(COPY) "$(LIB)" "$(PREFIX)/lib/$(LIB)"
	-if [ "x@DEBUGBUILD@" = xyes ] ; then $(COPY) "$(LIB_d)" "$(PREFIX)/lib/$(LIB_d)" ; fi
	$(COPY) sio.h usio.h "$(PREFIX)/include/"
	-chmod a+r "$(PREFIX)/lib/$(LIB)" "$(PREFIX)/lib/$(LIB_d)" "$(PREFIX)/include/sio.h" "$(PREFIX)/include/usio.h" 2>/dev/null
	-@$(LIST) "$(PREFIX)/lib/$(LIB)" "$(PREFIX)/lib/$(LIB_d)" "$(PREFIX)/include/sio.h" "$(PREFIX)/include/usio.h" 2>/dev/null

dynamic: $(LIBSO)

shared: $(LIBSO)

so: $(LIBSO)

$(LIBSO): $(SOBJS)
	$(DELETE) "$(LIBSO)" "$(LIBSOS)"
	$(CC) -shared "-Wl,-soname,$(LIBSO)" -o "$(LIBSO)" $(SOBJS)
	chmod a+r "$(LIBSO)" sio.h usio.h
	$(SYMLINK) "$(LIBSO)" "$(LIBSOS)"
	-@$(LIST) "$(LIBSOS)" "$(LIBSO)"

soinstall: $(LIBSO)
	$(COPY) "$(LIBSO)" "$(PREFIX)/lib/$(LIBSO)"
	$(DELETE) "$(PREFIX)/lib/$(LIBSOS)"
	( cd "$(PREFIX)/lib" ; $(SYMLINK) "$(LIBSO)" "$(LIBSOS)" )
	$(COPY) sio.h usio.h "$(PREFIX)/include"
	chmod a+r "$(PREFIX)/lib/$(LIBSO)" "$(PREFIX)/include/sio.h" "$(PREFIX)/include/usio.h"
	-@$(LIST) "$(PREFIX)/lib/$(LIBSO)" "$(PREFIX)/include/sio.h" "$(PREFIX)/include/usio.h"

ucase_c: ucase_c/ucase_c.c $(LIB)
	( cd ucase_c ; $(MAKE) "CFLAGS=$(CFLAGS)" "STRIP=$(STRIP)" "LIBS=$(LIBS)" )

ucase_s: ucase_s/ucase_s.c $(LIB)
	( cd ucase_s ; $(MAKE) "CFLAGS=$(CFLAGS)" "STRIP=$(STRIP)" "LIBS=$(LIBS)" )

srltest: srltest/srltest.c $(LIB)
	( cd srltest ; $(MAKE) "CFLAGS=$(CFLAGS)" "STRIP=$(STRIP)" "LIBS=$(LIBS)" )

time_c: time_c/time_c.c $(LIB)
	( cd time_c ; $(MAKE) "CFLAGS=$(CFLAGS)" "STRIP=$(STRIP)" "LIBS=$(LIBS)" )

time_s: time_s/time_s.c $(LIB)
	( cd time_s ; $(MAKE) "CFLAGS=$(CFLAGS)" "STRIP=$(STRIP)" "LIBS=$(LIBS)" )

samples: ucase_c ucase_s time_c time_s srltest

SHELL=/bin/sh
.SUFFIXES: .c .o .so

.c.o:
	@/Users/marianouvalle/dev/school/advanced_programming_ad2020/libncftp-3.2.6/libncftp/ccdv $(CC) $(CFLAGS) $(DEFS) $(CPPFLAGS) $< -c

.c.so:
	@/Users/marianouvalle/dev/school/advanced_programming_ad2020/libncftp-3.2.6/libncftp/ccdv $(CC) -fpic $(CFLAGS) $(DEFS) $(CPPFLAGS) $*.c -c -o $*.so

### Cleaning supplies ########################################################

clean:
	-$(DELETE) *.o *.so $(PCH) $(LIB) $(LIBSO) ucase_c/ucase_c ucase_s/ucase_s time_c/time_c time_s/time_s core *.pch */*.pch *.gch SunWS_cache

distclean: clean
	-$(DELETE) config.h Makefile config.status config.cache config.log sio.version autom4te.cache

### Archiving #################################################################

CFILES=\
	DNSUtil.c   main.c	 PRead.c	   PWrite.c \
	SAccept.c   SBind.c	 SClose.c	   SConnectByName.c \
	SConnect.c  SError.c	 SNew.c		   SocketUtil.c \
	SRead.c     SReadline.c  SRecv.c	   SRecvfrom.c \
	SRecvmsg.c  SSelect.c	 SSend.c	   SSendtoByName.c \
	SSendto.c   StrAddr.c	 SWait.c	   SWrite.c \
	UAccept.c   UBind.c	 UConnectByName.c  UConnect.c \
	UNew.c	    URecvfrom.c  USendtoByName.c   USendto.c

HFILES=sio.h usio.h

DOCFILES=sio.html
CFGFILES=config.h.in configure.in configure Makefile.in
CFGJUNK=config.h Makefile config.*
MOREJUNK=

# This is everything that is copied when you make a shar or tar.
PACKAGE=$(DOCFILES) $(HFILES) $(CFGFILES) $(MOREJUNK) $(CFILES)

TMPDIR=/tmp
TARDIR=sio-$(VER)
TARFILE=$(TARDIR).tar
TGZFILE=$(TARDIR).tar.gz

tarcp:
	-@$(MKDIR) $(TMPDIR)/TAR/$(TARDIR)
	-@chmod ga+r $(PACKAGE)
	-@chmod 755 $(TMPDIR)/TAR/$(TARDIR)
	$(COPY) $(PACKAGE) $(TMPDIR)/TAR/$(TARDIR)

tar: clean
	-@$(MKDIR) $(TMPDIR)/TAR
	-@$(MKDIR) $(TMPDIR)/TAR/$(TARDIR)
	-@chmod ga+r $(PACKAGE)
	find . -follow -depth -type f -print | cut -c3- | egrep -i -v '(((\.(o|so|log|a|lib|ncb|obj|exe|idb|cache|opt|zip|gz|swp|tar|plg|pch|gch))|((^|/)(config\.h|config\.status|Makefile|autoheader|autoconf)))$$|(/\.)|(^\.)|(xcuserdata|dSYM))' | cpio -Lpdm $(TMPDIR)/TAR/$(TARDIR)
	( cd $(TMPDIR)/TAR ; /usr/bin/tar cvf $(TARFILE) $(TARDIR) )
	$(COPY) $(TMPDIR)/TAR/$(TARFILE) .
	-@chmod 644 $(TARFILE)
	-@$(DELETE) $(TMPDIR)/TAR
	-@$(LIST) $(TARFILE)

gz: tar
	gzip -c $(TARFILE) > $(TGZFILE)
	-@$(DELETE) $(TARFILE)
	-@chmod 644 $(TGZFILE)
	-@$(LIST) $(TGZFILE)

### Dependencies #############################################################


SYSHDRS_DEP=syshdrs.h sio.h usio.h
PCH=

DNSUtil.o: DNSUtil.c $(SYSHDRS_DEP)
PRead.o: PRead.c $(SYSHDRS_DEP)
PWrite.o: PWrite.c $(SYSHDRS_DEP)
SAccept.o: SAccept.c $(SYSHDRS_DEP)
SBind.o: SBind.c $(SYSHDRS_DEP)
SClose.o: SClose.c $(SYSHDRS_DEP)
SConnect.o: SConnect.c $(SYSHDRS_DEP)
SConnectByName.o: SConnectByName.c $(SYSHDRS_DEP)
SNew.o: SNew.c $(SYSHDRS_DEP)
SRead.o: SRead.c $(SYSHDRS_DEP)
SReadline.o: SReadline.c $(SYSHDRS_DEP)
SRecv.o: SRecv.c $(SYSHDRS_DEP)
SRecvfrom.o: SRecvfrom.c $(SYSHDRS_DEP)
SRecvmsg.o: SRecvmsg.c $(SYSHDRS_DEP)
SSelect.o: SSelect.c $(SYSHDRS_DEP)
SSend.o: SSend.c $(SYSHDRS_DEP)
SSendto.o: SSendto.c $(SYSHDRS_DEP)
SSendtoByName.o: SSendtoByName.c $(SYSHDRS_DEP)
SWrite.o: SWrite.c $(SYSHDRS_DEP)
SWait.o: SWait.c $(SYSHDRS_DEP)
SocketUtil.o: SocketUtil.c $(SYSHDRS_DEP)
StrAddr.o: StrAddr.c $(SYSHDRS_DEP)
UAccept.o: UAccept.c $(SYSHDRS_DEP)
UBind.o: UBind.c $(SYSHDRS_DEP)
UConnect.o: UConnect.c $(SYSHDRS_DEP)
UConnectByName.o: UConnectByName.c $(SYSHDRS_DEP)
UNew.o: UNew.c $(SYSHDRS_DEP)
URecvfrom.o: URecvfrom.c $(SYSHDRS_DEP)
USendto.o: USendto.c $(SYSHDRS_DEP)
USendtoByName.o: USendtoByName.c $(SYSHDRS_DEP)
main.o: main.c $(SYSHDRS_DEP)
