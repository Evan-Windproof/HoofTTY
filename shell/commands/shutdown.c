/* SPDX-License-Identifier: GPL-3.0-or-later */

#include <kernseed/shell.h>
#include <kernseed/terminal.h>
#include <kernseed/io.h>

/*
 * Experimental QEMU PC/PIIX4 shutdown.
 *
 * Not a generic ACPI implementation.
 * Do not use this port on unknown hardware.
 */
#define QEMU_PM1_CNT_PORT 0x604
#define QEMU_SLP_EN       0x2000

static int shutdown_command_handler(int argc, char **argv) {
    (void)argc;
    (void)argv;

    terminal_write("Shutting down HoofTTY...\n");

    /* Request S5 power-off in the target QEMU setup. */
    outw(QEMU_PM1_CNT_PORT, QEMU_SLP_EN);

    /*
     * Reaching here means the request did not
     * immediately stop execution.
     */
    terminal_write(
        "error: shutdown request was not completed\n"
    );

    return 1;
}

REGISTER_COMMAND(
    shutdown_command,
    "shutdown",
    "Power off HoofTTY (QEMU PC only)",
    "shutdown",
    0, 0,
    shutdown_command_handler
);
