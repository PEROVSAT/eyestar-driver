#include "eyestar.h"

#include <errno.h>

int eyestar_init(eyestar_t *dev, const eyestar_config_t *cfg)
{
	if (dev == NULL || cfg == NULL) {
		return -EINVAL;
	}

	(void)cfg;

	/* FILL IN: probe the part, apply cfg, cache state on *dev.
	 * Call eyestar_transfer / eyestar_delay from
	 * lib/eyestar_bus.h. Do not add API functions in src/.
	 */

	return 0;
}
