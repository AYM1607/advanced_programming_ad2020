/* ../sio/config.h.  Generated automatically by configure.  */
/* config.h.in.  Generated automatically from configure.in by autoheader.  */

#define alarm_time_t unsigned int

/* #undef CAN_USE_SYS_SELECT_H */

/* Define if using alloca.c.  */
/* #undef C_ALLOCA */

/* Define to empty if the keyword does not work.  */
/* #undef const */

/* Define to one of _getb67, GETB67, getb67 for Cray-2 and Cray-YMP systems.
   This function is required for alloca.c support on those systems.  */
/* #undef CRAY_STACKSEG_END */

#define gethost_addrptr_t const struct in_addr *

#define gethostname_size_t size_t

/* Define if you have alloca, as a function or macro.  */
#define HAVE_ALLOCA 1

/* Define if you have <alloca.h> and it should be used (not on Ultrix).  */
#define HAVE_ALLOCA_H 1

/* #undef HAVE_MSGHDR_ACCRIGHTS */

#define HAVE_MSGHDR_CONTROL 1

/* Define if you have a _res global variable used by resolve routines. */
/* #undef HAVE__RES_DEFDNAME */

/* Define if you have sigsetjmp and siglongjmp. */
#define HAVE_SIGSETJMP 1

/* #undef HAVE_SOCKADDR_UN_SUN_LEN */

#define HAVE_STRUCT_CMSGDHR 1

#define HAVE_UNIX_DOMAIN_SOCKETS 1

#define listen_backlog_t int

#define main_void_return_t int

/* Define this because you definitely don't have it. Used only for testing configure. */
#define negative_control_t long

/* #undef PRAGMA_HDRSTOP */

#define read_return_t ssize_t

#define read_size_t size_t

#define recv_return_t ssize_t

#define recv_size_t size_t

/* #undef sa_family_t */

  
/* Define to the type of arg1 for select(). */
#define SELECT_TYPE_ARG1 int

/* Define to the type of args 2, 3 and 4 for select(). */
#define SELECT_TYPE_ARG234 (fd_set *)

/* Define to the type of arg5 for select(). */
#define SELECT_TYPE_ARG5 (struct timeval *)

#define send_return_t ssize_t

#define send_size_t size_t

/* Define to `int' if <sys/signal.h> doesn't define.  */
/* #undef sig_atomic_t */

/* Define to `unsigned' if <sys/types.h> doesn't define.  */
/* #undef size_t */

/* #undef SNPRINTF_RETURNS_PTR */

#define SNPRINTF_TERMINATES 1

#define sockaddr_size_t socklen_t

/* If SOCKS library is being used, define the major version (i.e. 5) */
/* #undef SOCKS */

#define sockopt_size_t socklen_t

/* Define to `long' if <sys/types.h> doesn't define.  */
/* #undef ssize_t */

/* If using the C implementation of alloca, define if you know the
   direction of stack growth for your system; otherwise it will be
   automatically deduced at run-time.
 STACK_DIRECTION > 0 => grows toward higher addresses
 STACK_DIRECTION < 0 => grows toward lower addresses
 STACK_DIRECTION = 0 => direction of growth unknown
 */
/* #undef STACK_DIRECTION */

/* Define if you have the ANSI C header files.  */
#define STDC_HEADERS 1

/* Define to the full path of the Tar program, if you have it. */
#define TAR "/usr/bin/tar"

/* Define if you can safely include both <sys/time.h> and <time.h>.  */
#define TIME_WITH_SYS_TIME 1

#define tv_sec_t long long

#define tv_usec_t int

#define write_return_t ssize_t

#define write_size_t size_t

/* Define if you have the getdomainname function.  */
#define HAVE_GETDOMAINNAME 1

/* Define if you have the gethostbyaddr_r function.  */
/* #undef HAVE_GETHOSTBYADDR_R */

/* Define if you have the gethostbyname_r function.  */
/* #undef HAVE_GETHOSTBYNAME_R */

/* Define if you have the gethostname function.  */
#define HAVE_GETHOSTNAME 1

/* Define if you have the getservbyname_r function.  */
/* #undef HAVE_GETSERVBYNAME_R */

/* Define if you have the getservbyport_r function.  */
/* #undef HAVE_GETSERVBYPORT_R */

/* Define if you have the inet_ntop function.  */
#define HAVE_INET_NTOP 1

/* Define if you have the recvmsg function.  */
#define HAVE_RECVMSG 1

/* Define if you have the sigaction function.  */
#define HAVE_SIGACTION 1

/* Define if you have the sigsetjmp function.  */
#define HAVE_SIGSETJMP 1

/* Define if you have the snprintf function.  */
#define HAVE_SNPRINTF 1

/* Define if you have the strerror function.  */
#define HAVE_STRERROR 1

/* Define if you have the vsnprintf function.  */
#define HAVE_VSNPRINTF 1

/* Define if you have the <arpa/nameser.h> header file.  */
#define HAVE_ARPA_NAMESER_H 1

/* Define if you have the <net/errno.h> header file.  */
/* #undef HAVE_NET_ERRNO_H */

/* Define if you have the <nserve.h> header file.  */
/* #undef HAVE_NSERVE_H */

/* Define if you have the <resolv.h> header file.  */
#define HAVE_RESOLV_H 1

/* Define if you have the <snprintf.h> header file.  */
/* #undef HAVE_SNPRINTF_H */

/* Define if you have the <socks.h> header file.  */
/* #undef HAVE_SOCKS_H */

/* Define if you have the <socks5p.h> header file.  */
/* #undef HAVE_SOCKS5P_H */

/* Define if you have the <strings.h> header file.  */
#define HAVE_STRINGS_H 1

/* Define if you have the <sys/socket.h> header file.  */
/* #undef HAVE_SYS_SOCKET_H */

/* Define if you have the <sys/time.h> header file.  */
#define HAVE_SYS_TIME_H 1

/* Define if you have the <sys/un.h> header file.  */
#define HAVE_SYS_UN_H 1

/* Define if you have the <time.h> header file.  */
#define HAVE_TIME_H 1

/* Define if you have the <unistd.h> header file.  */
#define HAVE_UNISTD_H 1

/* Define if you have the 44bsd library (-l44bsd).  */
/* #undef HAVE_LIB44BSD */

/* Define if you have the gen library (-lgen).  */
/* #undef HAVE_LIBGEN */

/* Define if you have the nsl library (-lnsl).  */
/* #undef HAVE_LIBNSL */

/* Define if you have the resolv library (-lresolv).  */
/* #undef HAVE_LIBRESOLV */

/* Define if you have the snprintf library (-lsnprintf).  */
/* #undef HAVE_LIBSNPRINTF */

/* Define if you have the socket library (-lsocket).  */
/* #undef HAVE_LIBSOCKET */
