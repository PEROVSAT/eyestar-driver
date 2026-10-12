#pragma once

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Device API. Adding a function:
 *   1. Declare it here
 *   2. Implement it in lib/eyestar.c
 *   3. Stub it in mock/eyestar.c
 *
 * Do not edit src/ for API work.
 */

typedef struct {
	/* FILL IN: DT-backed settings used by init. Remove if unused. */

} eyestar_config_t;

typedef struct eyestar {
	/*
	 * Which instance to talk to. src/ sets this to the Zephyr device
	 * pointer; unit tests set it to any non-NULL token. App code should
	 * not read or write it.
	 *
	 * The bus implementation is a named function (eyestar_transfer),
	 * not a pointer on this object. See lib/eyestar_bus.h.
	 */
	void *bus_ctx;

	/* FILL IN: cached chip state used after init. */
} eyestar_t;

int eyestar_init(eyestar_t *dev, const eyestar_config_t *cfg);
int eyestar_send_pkt(eyestar_t *dev, const uint8_t *pkt, size_t pkt_len);
int eyestar_fetch_pkt(eyestar_t *dev);
int eyestar_get_pkt(eyestar_t *dev, uint8_t *buf, size_t buf_capacity, size_t *pkt_len);
/* App glue: Zephyr `struct device` → this object. Implemented in src/. */
struct device;
eyestar_t *eyestar_from_dev(const struct device *dev);

#ifdef __cplusplus
}
#endif
