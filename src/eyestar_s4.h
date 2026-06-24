#pragma once

#define BOOT_STAGE    POST_KERNEL
#define BOOT_PRIORITY 100
// Put any other definitions here

#include <zephyr/device.h>

#if !defined(CONFIG_PEROVSAT_EYESTAR_S4_BACKEND_PUBLIC_MOCK)
	#include "eyestar_s4_lib.h"
#endif

typedef enum {
	FAIL_MODEM,
	FAIL_NETWORK,
	SENT
} tx_status_t;

typedef struct {
	bool uplinks_pending;
	size_t bytes_received;
	tx_status_t tx_status;
} eyestar_transfer_result_t;

// Since this driver is so direct, we are skipping doing the whole API struct,
// 	and just declaring this as a public function
#ifdef __cplusplus
extern "C" {
#endif

int eyestar_transfer(const struct device *dev, const uint8_t *tx_buf, size_t tx_len,
		     uint8_t *rx_buf, eyestar_transfer_result_t *res);

#ifdef __cplusplus
}
#endif

// Static config data, filled at init
struct eyestar_s4_config {
	// Mirror the devicetree properties here

#if defined(CONFIG_PEROVSAT_EYESTAR_S4_BACKEND_HARDWARE)
	// Add bus spec here
#endif
};

// Mutable state during runtime
struct eyestar_s4_data {
	// Things like cached samples go here

#if defined(CONFIG_PEROVSAT_EYESTAR_S4_BACKEND_SIMULATION)
	// Define things like a socket fd
#endif
};
