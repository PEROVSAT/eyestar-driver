#define DT_DRV_COMPAT nearspace_launch_eyestar_s4

#include "eyestar_s4.h"

#include <zephyr/device.h>
#include <zephyr/logging/log.h>

#if !defined(CONFIG_PEROVSAT_EYESTAR_S4_BACKEND_PUBLIC_MOCK)
	#include "transfer.h"
#endif

LOG_MODULE_REGISTER(eyestar_s4, CONFIG_LOG_DEFAULT_LEVEL);

// Static API functions that are defined in eyestar_s4.h get implemented here

/*
static int read_sensor(const struct device *dev, uint8_t *val)
{
	#if !defined(CONFIG_PEROVSAT_EYESTAR_S4_BACKEND_PUBLIC_MOCK)
		return eyestar_s4_lib_read_sensor(eyestar_s4_transfer, dev, val);
	#else
		ARG_UNUSED(dev);
		*val = 0x01;
		return 0;
	#endif
}
*/

const struct eyestar_s4_driver_api eyestar_s4_api = {
	// .read_sensor = read_sensor,
};

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
			      &eyestar_s4_config_##inst, BOOT_STAGE, BOOT_PRIORITY,                \
			      &eyestar_s4_api);

DT_INST_FOREACH_STATUS_OKAY(EYESTAR_S4_INIT)
