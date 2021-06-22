/**
 * @file ntop.c  Network address structure functions
 *
 * Copyright (C) 2010 Creytiv.com
 */

#define _BSD_SOURCE 1
#define _DEFAULT_SOURCE 1

#ifdef WIN32
#include <winsock2.h>
#else
#include <arpa/inet.h>
#endif /* WIN32 */
#include <string.h>
#include <re_types.h>
#include <re_fmt.h>
#include <re_mbuf.h>
#include <re_sa.h>
#include "sa.h"


#define DEBUG_MODULE "net_ntop"
#define DEBUG_LEVEL 5
#include <re_dbg.h>


/**
 * Convert network address structure to a character string
 *
 * @param sa   Socket address
 * @param buf  Buffer to return IP address
 * @param size Size of buffer
 *
 * @return 0 if success, otherwise errorcode
 */
int net_inet_ntop(const struct sa *sa, char *buf, int size)
{
	if (!sa || !buf || !size)
		return EINVAL;

	switch (sa->u.sa.sa_family) {

	case AF_INET:
		inet_ntop(AF_INET, &sa->u.in.sin_addr, buf, size);
		break;

#ifdef HAVE_INET6
	case AF_INET6:
		inet_ntop(AF_INET6, &sa->u.in6.sin6_addr, buf, size);
		break;
#endif

	default:
		return EAFNOSUPPORT;
	}

	return 0;
}
