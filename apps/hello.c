/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "abi.h"
void _start(void){write_text("Hello from HoofTTY userspace!\n");
	finish();
}
