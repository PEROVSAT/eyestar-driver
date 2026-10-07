/*
 * Unit tests for the portable device library.
 *
 * Links lib/eyestar.c only. Do not use src/. When a test talks to
 * the bus, define eyestar_transfer and eyestar_delay in
 * this file (see lib/eyestar_bus.h).
 */

#include <zephyr/ztest.h>

#if 0
	#include "eyestar.h"
	#include "eyestar_bus.h"

int eyestar_transfer(void *ctx, uint8_t reg, uint8_t *buf, size_t len, bool read)
{
	ARG_UNUSED(ctx);
	ARG_UNUSED(reg);
	ARG_UNUSED(buf);
	ARG_UNUSED(len);
	ARG_UNUSED(read);

	return 0;
}

void eyestar_delay(uint32_t ms)
{
	ARG_UNUSED(ms);
}

ZTEST(eyestar_unit, test_init)
{
	eyestar_t dev = {
		.bus_ctx = (void *)1,
	};
	eyestar_config_t cfg = {0};

	zassert_ok(eyestar_init(&dev, &cfg));
}
#endif

ZTEST_SUITE(eyestar_unit, NULL, NULL, NULL, NULL, NULL);
