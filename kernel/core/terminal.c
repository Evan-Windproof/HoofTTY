/* SPDX-License-Identifier: GPL-3.0-or-later */
#include <kernseed/terminal.h>
#include <kernseed/console.h>
/* One shell task owns interactive display. Never called by keyboard IRQ. */
static bool cursor_enabled = false;

void terminal_cursor_enable(bool enabled) {
    framebuffer_cursor_hide();
    cursor_enabled = enabled;

    if (cursor_enabled)
        framebuffer_cursor_show();
}

void terminal_write(const char *s) {
    if (cursor_enabled)
        framebuffer_cursor_hide();

    console_write(s);

    if (cursor_enabled)
        framebuffer_cursor_show();
}

void terminal_clear(void){
    if (cursor_enabled)
        framebuffer_cursor_hide();
}
void terminal_erase(void){
    framebuffer_backspace();
    serial_putc('\b');
    serial_putc(' ');
    serial_putc('\b');
}

void terminal_dec(uint64_t value){
    char text[21];
    unsigned at=20;
    text[at]=0;
    do{text[--at]=(char)('0'+value%10);value/=10;}
    while(value);
    terminal_write(text+at);
}

void terminal_set_color(uint8_t color) {
    framebuffer_set_color(color);
}
