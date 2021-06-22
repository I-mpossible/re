/**
 * @file pton.c  Network address structure functions
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


#define DEBUG_MODULE "net_pton"
#define DEBUG_LEVEL 5
#include <re_dbg.h>


/**
 * Convert character string to a network address structure
 *
 * @param addr IP address string
 * @param sa   Returned socket address
 *
 * @return 0 if success, otherwise errorcode
 */
int net_inet_pton(const char *addr, struct sa *sa)
{
	if (!addr)
		return EINVAL;

	if (inet_pton(AF_INET, addr, &sa->u.in.sin_addr) > 0) {
		sa->u.in.sin_family = AF_INET;
	}
#ifdef HAVE_INET6
	else if (inet_pton(AF_INET6, addr, &sa->u.in6.sin6_addr) > 0) {

		if (IN6_IS_ADDR_V4MAPPED(&sa->u.in6.sin6_addr)) {
			const uint8_t *a = &sa->u.in6.sin6_addr.s6_addr[12];
			sa->u.in.sin_family = AF_INET;
			memcpy(&sa->u.in.sin_addr.s_addr, a, 4);
		}
		else {
			sa->u.in6.sin6_family = AF_INET6;
		}
	}
#endif
	else {
		return EINVAL;
	}

	return 0;
}
