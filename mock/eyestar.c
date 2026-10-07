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

int eyestar_send_pkt(eyestar_t *dev, const uint8_t *pkt) // Telling the Eyestar to send a packet
{
	(void)dev;
	(void)pkt;

	return 0;
}

int eyestar_fetch_pkt(eyestar_t *dev, uint8_t *pkt)
{
	(void)dev;
	if (pkt == NULL) {
		return -1;
	}
	return 0;
}

int eyestar_get_pkt(eyestar_t *dev, uint8_t *pkt)
{
	(void)dev;

	return 0;
}
