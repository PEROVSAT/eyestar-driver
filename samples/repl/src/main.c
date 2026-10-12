#include <zephyr/device.h>
#include <zephyr/shell/shell.h>

#include <errno.h>
#include <string.h>

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

static int sh_ret(const struct shell *sh, int ret)
{
	if (ret < 0) {
		shell_error(sh, "error %d", ret);
		return ret;
	}

	return 0;
}

static void print_config(const struct shell *sh, const eyestar_config_t *cfg)
{
	if (cfg == NULL) {
		shell_error(sh, "config is NULL");
		return;
	}
	shell_print(sh, "eyestar_config_t {");
	shell_print(sh, "}");
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

static int cmd_send_pkt(const struct shell *sh, size_t argc, char **argv)
{
	eyestar_t *dev = sh_dev(sh);
	uint8_t pkt[256];
	size_t pkt_len;
	int ret;

	if (dev == NULL) {
		return -ENODEV; // Nothing found
	}

	if (argc != 2) {
		shell_error(sh, "Usage: eyestar send_pkt <hex bytes>");
		return -EINVAL;
	}

	/* Parse the hex bytes into the packet buffer */
	pkt_len = hex2bin(argv[1], strlen(argv[1]), pkt, sizeof(pkt));
	if (pkt_len == 0) {
		shell_error(sh, "Invalid hex bytes");
		return -EINVAL;
	}

	ret = eyestar_send_pkt(dev, pkt, pkt_len);
	if (ret < 0) {
		shell_error(sh, "Failed to send packet: %d", ret);
		return ret;
	}
	shell_print(sh, "Packet sent successfully");
	return 0;
}

static int cmd_fetch_pkt(const struct shell *sh, size_t argc, char **argv)
{
	eyestar_t *dev = sh_dev(sh);
	int ret;
	ARG_UNUSED(argc);
	ARG_UNUSED(argv);

	if (dev == NULL) {
		return -ENODEV; // Nothing found
	}

	ret = eyestar_fetch_pkt(dev);
	if (ret < 0) {
		shell_error(sh, "Failed to fetch packet: %d", ret);
		return ret;
	}
	shell_print(sh, "Packet fetched successfully");
	return 0;
}

static int cmd_get_pkt(const struct shell *sh, size_t argc, char **argv)
{
	eyestar_t *dev = sh_dev(sh);
	uint8_t pkt[256];
	size_t pkt_len;
	int ret;
	ARG_UNUSED(argc);
	ARG_UNUSED(argv);

	if (dev == NULL) {
		return -ENODEV; // Nothing found
	}

	ret = eyestar_get_pkt(dev, pkt, sizeof(pkt), &pkt_len);
	if (ret < 0) {
		shell_error(sh, "Failed to get packet: %d", ret);
		return ret;
	}

	shell_print(sh, "Packet received (%u bytes):", (unsigned int)pkt_len);
	shell_hexdump(sh, pkt, pkt_len);
	return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(eyestar_cmds,
			       SHELL_CMD(status, NULL, "Check the driver is ready", cmd_status),
			       SHELL_CMD(send_pkt, NULL, "Send a packet", cmd_send_pkt),
			       SHELL_CMD(fetch_pkt, NULL, "Fetch a packet", cmd_fetch_pkt),
			       SHELL_CMD(get_pkt, NULL, "Get a packet", cmd_get_pkt),
			       SHELL_SUBCMD_SET_END);

SHELL_CMD_REGISTER(eyestar, &eyestar_cmds, "EYESTAR driver", NULL);

int main(void)
{
	return 0;
}
