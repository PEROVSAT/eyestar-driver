# eyestar-driver

Device library for **EYESTAR**, wrapped as a Zephyr module.

The bus is a named function (`eyestar_transfer` in
`lib/eyestar_bus.h`), defined at link time — not a pointer on the
device object. I2C, SPI, and UART belong in `src/hardware_transfer.c`. Change
the transfer signature if the device is not a register map.

## Where to write code

| File | Role |
|------|------|
| `include/eyestar.h` | API — types and function prototypes |
| `lib/eyestar.c` | Real implementations |
| `lib/eyestar_bus.h` | Named bus functions (`transfer`, `delay`) |
| `lib/eyestar_regs.h` | Protocol constants |
| `mock/eyestar.c` | Same symbols, canned values (NDA-safe CI) |

**Adding a function:** declare it in the header, implement it in `lib/`, stub it in `mock/`. Do not edit `src/` for API work.

`src/` is Zephyr packaging (DT, bus bind, `from_dev`). Open it when bringing the chip up, not when adding API functions.

## Backends

Kconfig selects exactly one. Public mock links `mock/`. The other two link `lib/` and supply `eyestar_transfer` at link time.

| Backend | Links | `eyestar_transfer` comes from |
|---------|-------|--------------------------------------|
| Public mock (default) | `mock/eyestar.c` | not used |
| Library mock | `lib/eyestar.c` | `src/lib_mock_transfer.c` |
| Hardware | `lib/eyestar.c` | `src/hardware_transfer.c` |

App code:

```c
#include <eyestar.h>

eyestar_t *dev = eyestar_from_dev(DEVICE_DT_GET(DT_ALIAS(eyestar)));
```

Do not call `eyestar_init()` from the app. Driver init already ran at boot.

## Tests and REPL

From a west workspace that includes this module and `hal_rpi_pico`:

```bash
west twister -T tests/unit -p qemu_cortex_m3
west build -b rpi_pico2/rp2350a/m33 eyestar-driver/samples/repl
west flash -r uf2
```

The REPL sample defaults to Pico 2 and the UF2 runner. `west flash` with no `-r` uses OpenOCD (SWD probe). UF2 needs BOOTSEL: unplug USB, hold BOOTSEL, plug in, wait for the `RP2350` volume, then flash. After reset the shell is `/dev/cu.usbmodem*` (not a `cu.USB_*` name). Close any serial session before the next BOOTSEL cycle.

The sample overlay keeps the device node and USB CDC console in `app.overlay`. Do not put CDC only in `boards/*.overlay` — that replaces `app.overlay` and drops `DT_HAS_*`.

Unit tests compile `lib/` only. Uncomment the example in `tests/unit` and add
`eyestar_transfer` there when tests need a bus. They do not enable the
Zephyr driver. Twister also allows `rpi_pico2/rp2350a/m33` for on-desk runs.

## App integration (perovsat-app)

1. Add this repo as a west project.
2. Snippet `.conf`: `CONFIG_PEROVSAT_EYESTAR=y` and a backend.
3. Devicetree node with `compatible = "nearspacelaunch,eyestar"`. Put it on I2C/SPI/UART when filling in hardware.
