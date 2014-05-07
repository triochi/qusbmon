/*
 * types.h
 *
 *  Created on: Feb 28, 2009
 *      Author: archivator
 */

#ifndef TYPES_H_
#define TYPES_H_

#include <QMetaType>

typedef signed int s32;
typedef unsigned int u32;
typedef signed long long s64;
typedef unsigned long long u64;

struct mon_bin_hdr {
	u64 id;			/* URB ID - from submission to callback */
	unsigned char type;	/* Same as in text API; extensible. */
	unsigned char xfer_type;	/* ISO, Intr, Control, Bulk */
	unsigned char endpoint;	/* Endpoint number and transfer direction */
	unsigned char device;	/* Device address */
	unsigned short bus;	/* Bus number */
	char flag_setup;
	char flag_data;
	s64 ts_sec;		/* gettimeofday */
	s32 ts_usec;		/* gettimeofday */
	int status;
	unsigned int lengthUrb;	/* Length of data (submitted or actual) */
	unsigned int lengthCaptured;	/* Delivered length */
	unsigned char setup[8];	/* Only for Control S-type */
};
struct mon_bin_get {
	struct mon_bin_hdr *header;	/* Only 48 bytes, not 64. */
	void *data;
	size_t length;		/* Length of data (can be zero) */
};

struct mon_bin_stats {
	u32 queued;
	u32 dropped;
};

#endif /* TYPES_H_ */
