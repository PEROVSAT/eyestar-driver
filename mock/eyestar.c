/*
 * Public fake of the device API. Same symbols as lib/eyestar.c;
 * CMake links exactly one of the two.
 */

#include "eyestar.h"

#include <stddef.h>

int eyestar_init(eyestar_t *dev, const eyestar_config_t *cfg)
{
	(void)dev;
	(void)cfg;
	return 0;
}

int eyestar_send_pkt(eyestar_t *dev, const uint8_t *pkt,
		     size_t pkt_len) // Telling the Eyestar to send a packet
{
	return 0;
}

int eyestar_fetch_pkt(eyestar_t *dev)
{
	if (dev == NULL) {
		return -1;
	}
	return 0;
}

int eyestar_get_pkt(eyestar_t *dev, uint8_t *buf, size_t buf_capacity, size_t *pkt_len)
{
	if (dev == NULL) {
		return -1;
	}
	if (buf == NULL) {
		return -1;
	}
	if (pkt_len == NULL) {
		return -1;
	}
	if (buf_capacity == 0) {
		return -1;
	}
	return 0;
}
