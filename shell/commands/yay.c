/* SPDX-License-Identifier: GPL-3.0-or-later */
#include <kernseed/shell.h>
#include <kernseed/terminal.h>
#include <kernseed/console.h>

static int yay(int argc, char **argv) {
    (void)argc;
    (void)argv;
    
    framebuffer_set_color(14);
    terminal_write("...yay.\n");
    return 0;
}

REGISTER_COMMAND(
    yay_command,
    "yay",
    "A tiny cheer from Fluttershy",
    "yay",
    0, 0,
    yay
);
