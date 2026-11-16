/* SPDX-License-Identifier: GPL-3.0-or-later */
#include <kernseed/shell.h>
#include <kernseed/terminal.h>
#include <kernseed/console.h>

static int party(int argc, char **argv) {
    (void)argc;
    (void)argv;

	framebuffer_set_color(13);
	terminal_write("Surprise!\n");

	framebuffer_set_color(13);
	terminal_write("* * * PARTY TIME! * * *\n");
	return 0;
}

REGISTER_COMMAND(
    party_command,
    "party",
    "Pinkie Pie's party",
    "party",
    0, 0,
    party
);
