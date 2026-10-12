/*
 * Zephyr packaging: apply DT, bind the bus, call eyestar_init().
 * Do not add device functions here. See include/eyestar.h.
 */

#define DT_DRV_COMPAT nearspacelaunch_eyestar

#include "eyestar_priv.h"

#if !defined(CONFIG_PEROVSAT_EYESTAR_BACKEND_PUBLIC_MOCK)
	#include "eyestar_bus.h"
#endif

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(eyestar, CONFIG_LOG_DEFAULT_LEVEL);

eyestar_t *eyestar_from_dev(const struct device *dev)
{
	struct eyestar_driver_data *data = dev->data;

	return &data->chip;
}

#if !defined(CONFIG_PEROVSAT_EYESTAR_BACKEND_PUBLIC_MOCK)
void eyestar_delay(uint32_t ms)
{
	k_msleep(ms);
}
#endif

static int eyestar_driver_init(const struct device *dev)
{
	struct eyestar_driver_data *data = dev->data;
	const struct eyestar_driver_config *cfg = dev->config;

#if !defined(CONFIG_PEROVSAT_EYESTAR_BACKEND_PUBLIC_MOCK)
	int ret;

	data->chip.bus_ctx = (void *)dev;

	ret = eyestar_transfer_init(dev);
	if (ret < 0) {
		return ret;
	}
#endif

	return eyestar_init(&data->chip, &cfg->chip);
}

#define EYESTAR_INIT(inst)                                                                         \
	static struct eyestar_driver_data eyestar_data_##inst;                                     \
	static const struct eyestar_driver_config eyestar_config_##inst = {                        \
		.chip = {},                                                                        \
	};                                                                                         \
	DEVICE_DT_INST_DEFINE(inst, eyestar_driver_init, NULL, &eyestar_data_##inst,               \
			      &eyestar_config_##inst, BOOT_STAGE, BOOT_PRIORITY, NULL);

DT_INST_FOREACH_STATUS_OKAY(EYESTAR_INIT)
