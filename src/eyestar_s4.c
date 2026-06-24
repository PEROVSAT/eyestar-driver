#define DT_DRV_COMPAT nearspace_launch_eyestar_s4

#include "eyestar_s4.h"

#include <zephyr/device.h>
#include <zephyr/logging/log.h>

#if !defined(CONFIG_PEROVSAT_EYESTAR_S4_BACKEND_PUBLIC_MOCK)
	#include "transfer.h"
#endif

LOG_MODULE_REGISTER(eyestar_s4, CONFIG_LOG_DEFAULT_LEVEL);

// Public API functions that are defined in eyestar_s4.h get implemented here

int eyestar_transfer(const struct device *dev, const uint8_t *tx_buf, size_t tx_len,
		     uint8_t *rx_buf, eyestar_transfer_result_t *res)
{
#if !defined(CONFIG_PEROVSAT_EYESTAR_S4_BACKEND_PUBLIC_MOCK)
	return 0; // Not implemented
#else
	res->uplinks_pending = 0;
	res->bytes_received = 0;
	res->tx_status = SENT;
	return 0;
#endif
}

static int eyestar_s4_init(const struct device *dev)
{
#if !defined(CONFIG_PEROVSAT_EYESTAR_S4_BACKEND_PUBLIC_MOCK)
	// Initialize transfer backend and library
	int ret = eyestar_s4_transfer_init(dev);
	if (ret < 0) {
		return ret;
	}

	return eyestar_s4_lib_init(eyestar_s4_transfer, dev);
#else
	ARG_UNUSED(dev);
	return 0;
#endif
}

#define EYESTAR_S4_INIT(inst)                                                                      \
	static struct eyestar_s4_data eyestar_s4_data_##inst;                                      \
	static const struct eyestar_s4_config eyestar_s4_config_##inst = {                         \
		/* FILL IN: .bus = I2C_DT_SPEC_INST_GET(inst), */                                  \
	};                                                                                         \
	DEVICE_DT_INST_DEFINE(inst, eyestar_s4_init, NULL, &eyestar_s4_data_##inst,                \
			      &eyestar_s4_config_##inst, BOOT_STAGE, BOOT_PRIORITY, NULL);

DT_INST_FOREACH_STATUS_OKAY(EYESTAR_S4_INIT)
