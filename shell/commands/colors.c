/* SPDX-License-Identifier: PolyForm-Noncommercial-1.0.0 */
#include <kernseed/shell.h>
#include <kernseed/terminal.h>

static int colors(int argc, char **argv) {
	(void)argc;
	(void)argv;

	static const char *name[16] = {
		"Black", "Red", "Green", "Yellow/Brown",
		"Blue", "Magenta", "Cyan", "Light Gray",
		"Dark Gray", "Bright Red", "Bright Green",
		"Bright Yellow", "Bright Blue",
		"Bright Magenta", "Bright Cyan", "White"
	};

	terminal_write("HoofTTY 16-color palette:\n\n");

	for (unsigned i = 0; i < 16; ++i) {
		terminal_set_color((uint8_t)i);
		terminal_write(name[i]);
		terminal_write("\n");

	}

	/* Restore the default light foreground. */
	terminal_set_color(7);
	return 0;
}

REGISTER_COMMAND(
	colors_command,
	"colors",
	"Display the 16-color termianl palette",
	"colors",
	0, 0,
	colors
);
