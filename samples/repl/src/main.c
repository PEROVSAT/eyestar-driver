#include <zephyr/device.h>
#include <zephyr/shell/shell.h>

#include <eyestar.h>

static eyestar_t *sh_dev(const struct shell *sh)
{
	const struct device *zdev = DEVICE_DT_GET(DT_ALIAS(eyestar));

	if (!device_is_ready(zdev)) {
		shell_error(sh, "device not ready");
		return NULL;
	}

	return eyestar_from_dev(zdev);
}

static int cmd_status(const struct shell *sh, size_t argc, char **argv)
{
	eyestar_t *dev = sh_dev(sh);

	ARG_UNUSED(argc);
	ARG_UNUSED(argv);

	if (dev == NULL) {
		return -ENODEV;
	}

	/* FILL IN: call other public APIs via this same from_dev handle. */
	shell_print(sh, "ready");
	return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(eyestar_cmds,
			       SHELL_CMD(status, NULL, "Check the driver is ready", cmd_status),
			       SHELL_SUBCMD_SET_END);

SHELL_CMD_REGISTER(eyestar, &eyestar_cmds, "EYESTAR driver", NULL);

int main(void)
{
	return 0;
}
