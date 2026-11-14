/* SPDX-License-Identifier: PolyForm-Noncommercial-1.0.0 */
#include <kernseed/shell.h>
#include <kernseed/terminal.h>
static int clear(int argc,char **argv){
    (void)argc;
    (void)argv;
    terminal_clear();
    return 0;
}
REGISTER_COMMAND(clear_command,"rainboom","Rainboom","rainboom [arg]",0,0,clear);
