/* SPDX-License-Identifier: GPL-3.0-or-later */
#include <kernseed/console.h>
#include <limine.h>
#include <stddef.h>

/* Original 5x7 bitmap alphabet. Lowercase is displayed as uppercase.
 * Each row occupies five low bits, leftmost pixel in bit 4. No font dependency. */
static const uint8_t font[128][7] = {
    ['A']={14,17,17,31,17,17,17}, ['B']={30,17,17,30,17,17,30},
    ['C']={14,17,16,16,16,17,14}, ['D']={30,17,17,17,17,17,30},
    ['E']={31,16,16,30,16,16,31}, ['F']={31,16,16,30,16,16,16},
    ['G']={14,17,16,23,17,17,15}, ['H']={17,17,17,31,17,17,17},
    ['I']={14,4,4,4,4,4,14}, ['J']={7,2,2,2,18,18,12},
    ['K']={17,18,20,24,20,18,17}, ['L']={16,16,16,16,16,16,31},
    ['M']={17,27,21,21,17,17,17}, ['N']={17,25,21,19,17,17,17},
    ['O']={14,17,17,17,17,17,14}, ['P']={30,17,17,30,16,16,16},
    ['Q']={14,17,17,17,21,18,13}, ['R']={30,17,17,30,20,18,17},
    ['S']={15,16,16,14,1,1,30}, ['T']={31,4,4,4,4,4,4},
    ['U']={17,17,17,17,17,17,14}, ['V']={17,17,17,17,17,10,4},
    ['W']={17,17,17,21,21,21,10}, ['X']={17,17,10,4,10,17,17},
    ['Y']={17,17,10,4,4,4,4}, ['Z']={31,1,2,4,8,16,31},
    ['0']={14,17,19,21,25,17,14}, ['1']={4,12,4,4,4,4,14},
    ['2']={14,17,1,2,4,8,31}, ['3']={30,1,1,14,1,1,30},
    ['4']={2,6,10,18,31,2,2}, ['5']={31,16,16,30,1,1,30},
    ['6']={14,16,16,30,17,17,14}, ['7']={31,1,2,4,8,8,8},
    ['8']={14,17,17,14,17,17,14}, ['9']={14,17,17,15,1,1,14},
    ['.']={0,0,0,0,0,6,6}, [':']={0,6,6,0,6,6,0},
    ['-']={0,0,0,31,0,0,0}, ['/']={1,2,2,4,8,8,16},
    ['[']={14,8,8,8,8,8,14}, [']']={14,2,2,2,2,2,14},
    ['=']={0,0,31,0,31,0,0}, ['?']={14,17,1,2,4,0,4},
    ['_']={0,0,0,0,0,0,31}, ['(']={2,4,8,8,8,4,2},
    [')']={8,4,2,2,2,4,8}, ['!']={4,4,4,4,4,0,4},
    ['>']={16,8,4,2,4,8,16}, ['<']={1,2,4,8,4,2,1},
    ['\'']={4,4,0,0,0,0,0}, ['\"']={10,10,0,0,0,0,0},
    [',']={0,0,0,0,6,4,8}, [';']={0,6,6,0,6,4,8},
    ['+']={0,4,4,31,4,4,0}, ['\\']={16,8,8,4,2,2,1},
    ['a']={0,0,14,1,15,17,15}, ['b']={16,16,22,25,17,17,30},
    ['c']={0,0,14,17,16,17,14}, ['d']={1,1,13,19,17,17,15},
    ['e']={0,0,14,17,31,16,14}, ['f']={6,9,8,28,8,8,8},
    ['g']={0,0,15,17,15,1,14}, ['h']={16,16,22,25,17,17,17},
    ['i']={4,0,12,4,4,4,14}, ['j']={2,0,6,2,2,18,12},
    ['k']={16,16,18,20,24,20,18}, ['l']={12,4,4,4,4,4,14},
    ['m']={0,0,26,21,21,21,21}, ['n']={0,0,22,25,17,17,17},
    ['o']={0,0,14,17,17,17,14}, ['p']={0,0,30,17,30,16,16},
    ['q']={0,0,13,19,15,1,1}, ['r']={0,0,22,25,16,16,16},
    ['s']={0,0,15,16,14,1,30}, ['t']={8,8,28,8,8,9,6},
    ['u']={0,0,17,17,17,19,13}, ['v']={0,0,17,17,17,10,4},
    ['w']={0,0,17,17,21,21,21}, ['x']={0,0,17,10,4,10,17},
    ['y']={0,0,17,17,15,1,14}, ['z']={0,31,2,4,8,16,31},
    ['~'] = {0,0,9,22,0,0,0}, ['`'] = {8,4,0,0,0,0,0},
    ['@'] = {14,17,23,21,23,16,14}, ['#'] = {10,10,31,10,31,10,10},
    ['$'] = {4,15,20,14,5,30,4}, ['%'] = {17,2,4,8,16,17,0},
    ['&'] = {12,18,20,8,21,18,13}, ['*'] = {0,21,14,31,14,21,0},
    ['^'] = {4,10,17,0,0,0,0},
};


static const uint32_t ansi_palette[16] = {
    0x000000, 0xAA0000, 0x00AA00, 0xAA5500,
    0x0000AA, 0xAA00AA, 0x00AAAA, 0xAAAAAA,
    0x555555, 0xFF5555, 0x55FF55, 0xFFFF55,
    0x5555FF, 0xFF55FF, 0x55FFFF, 0xFFFFFF
};


static struct limine_framebuffer *screen;
static uint64_t column, row;
static uint32_t foreground;
enum { 
    CELL_W = 12, 
    CELL_H = 18 
};

enum {
    CURSOR_W = 10,
    CURSOR_H = 2
};

static bool cursor_visible;
static uint64_t cursor_x, cursor_y;
static uint32_t cursor_saved[CURSOR_W * CURSOR_H];

static void pixel(uint64_t x, uint64_t y, uint32_t color) {
    volatile uint32_t *p = (volatile uint32_t *)((uint8_t *)screen->address
                                               + y * screen->pitch + x * 4);
    *p = color;
}

void framebuffer_cursor_hide(void) {
    if (!screen || !cursor_visible)
        return;

    for (unsigned y = 0; y < CURSOR_H; ++y) {
        for (unsigned x = 0; x < CURSOR_W; ++x) {
            pixel(
                cursor_x + x,
                cursor_y + y,
                cursor_saved[y * CURSOR_W + x]
            );
        }
    }

    cursor_visible = false;
}

void framebuffer_cursor_show(void) {
    if (!screen || cursor_visible)
        return;

    uint64_t x = column * CELL_W + 1;
    uint64_t y = row * CELL_H + CELL_H - 3;

    if (x >= screen->width ||
        y >= screen->height ||
        CURSOR_W > screen->width - x ||
        CURSOR_H > screen->height - y)
        return;

    cursor_x = x;
    cursor_y = y;

    uint32_t rgb = 0x55FF55;

    uint32_t color =
        (0x55U << screen->red_mask_shift) |
        (0xFFU << screen->green_mask_shift) |
        (0x55U << screen->blue_mask_shift);

    (void)rgb;

    for (unsigned py = 0; py < CURSOR_H; ++py) {
        for (unsigned px = 0; px < CURSOR_W; ++px) {
            uint64_t dx = x + px;
            uint64_t dy = y + py;

            volatile uint32_t *source =
                (volatile uint32_t *)(
                    (uint8_t *)screen->address +
                    dy * screen->pitch +
                    dx * 4
                );

            cursor_saved[py * CURSOR_W + px] = *source;
            pixel(dx, dy, color);
        }
    }

    cursor_visible = true;
}

static void clear(void) {
    for (uint64_t y = 0; y < screen->height; ++y)
        for (uint64_t x = 0; x < screen->width; ++x) pixel(x, y, 0);
    column = row = 0;
}

bool framebuffer_init(struct limine_framebuffer *fb) {
    /* Phase 1 supports RGB 32bpp, byte-aligned 8-bit channels. */
    if (!fb || !fb->address || ((uintptr_t)fb->address & 3) || fb->bpp != 32 || fb->memory_model != 1 ||
        fb->red_mask_size != 8 || fb->green_mask_size != 8 || fb->blue_mask_size != 8 ||
        fb->red_mask_shift > 24 || fb->green_mask_shift > 24 || fb->blue_mask_shift > 24 ||
        fb->red_mask_shift % 8 || fb->green_mask_shift % 8 || fb->blue_mask_shift % 8 ||
        fb->red_mask_shift == fb->green_mask_shift || fb->red_mask_shift == fb->blue_mask_shift ||
        fb->green_mask_shift == fb->blue_mask_shift || fb->width < CELL_W ||
        fb->height < CELL_H || fb->width > 8192 || fb->height > 8192 ||
        fb->pitch < fb->width * 4 || fb->pitch > 65536 || fb->pitch % 4) return false;
    screen = fb;
    cursor_visible = false;
    foreground = (0xddU << fb->red_mask_shift) | (0xeeU << fb->green_mask_shift)
               | (0xffU << fb->blue_mask_shift);
    clear();
    return true;
}

void framebuffer_putc(char c) {
    if (!screen) return;
    if (c == '\r') { column = 0; return; }
    if (c == '\n') { column = 0; ++row; }
    else {
        if ((unsigned char)c >= 128 || (c < ' ')) c = '?';
        uint64_t x = column * CELL_W, y = row * CELL_H;
        for (unsigned dy = 0; dy < CELL_H; ++dy)
            for (unsigned dx = 0; dx < CELL_W; ++dx) {
                bool lit = dx < 10 && dy < 14 &&
                           (font[(unsigned char)c][dy / 2] & (1U << (4 - dx / 2)));
                pixel(x + dx, y + dy, lit ? foreground : 0);
            }
        if (++column == screen->width / CELL_W) { column = 0; ++row; }
    }
    if (row == screen->height / CELL_H) {
        uint64_t text_height=(screen->height/CELL_H)*CELL_H;
        for(uint64_t y=0;y<text_height-CELL_H;y++)
            for(uint64_t x=0;x<screen->width;x++){
                volatile uint32_t *source=(volatile uint32_t *)((uint8_t *)screen->address+(y+CELL_H)*screen->pitch+x*4);
                pixel(x,y,*source);
            }
        for(uint64_t y=text_height-CELL_H;y<screen->height;y++)
            for(uint64_t x=0;x<screen->width;x++)pixel(x,y,0);
        row--;
    }
}

void framebuffer_clear(void){if(screen)clear();}
void framebuffer_backspace(void){
    if(!screen)return;
    if(column)column--;
    else if(row){row--;column=screen->width/CELL_W-1;}
    else return;
    for(unsigned y=0;y<CELL_H;y++)for(unsigned x=0;x<CELL_W;x++)pixel(column*CELL_W+x,row*CELL_H+y,0);
}

void framebuffer_set_color(uint8_t index) {
    if (!screen || index >= 16)
        return;

    uint32_t rgb = ansi_palette[index];

    uint32_t r = (rgb >> 16) & 0xFF;
    uint32_t g = (rgb >> 8) & 0xFF;
    uint32_t b = rgb & 0xFF;

    foreground =
        (r << screen->red_mask_shift) |
        (g << screen->green_mask_shift) |
        (b << screen->blue_mask_shift);
}


void framebuffer_draw_sprite(
    uint32_t x,
    uint32_t y,
    uint32_t width,
    uint32_t height,
    const uint8_t *pixels,
    uint32_t scale
) {
    if (!screen || !pixels || !scale || !width || !height)
        return;

    if (x >= screen->width || y >= screen->height)
        return;

    for (uint32_t py = 0; py < height; ++py) {
        for (uint32_t px = 0; px < width; ++px) {

            uint8_t index = pixels[(size_t)py * width + px];

            /* 255 means transparent. */
            if (index == 255 || index >= 16)
                continue;

            uint32_t rgb = ansi_palette[index];

            uint32_t r = (rgb >> 16) & 0xFF;
            uint32_t g = (rgb >> 8) & 0xFF;
            uint32_t b = rgb & 0xFF;

            uint32_t color =
                (r << screen->red_mask_shift) |
                (g << screen->green_mask_shift) |
                (b << screen->blue_mask_shift);

            /* Draw each sprite pixel at the requested scale. */
            for (uint32_t sy = 0; sy < scale; ++sy) {
                uint64_t dy = (uint64_t)y +
                              (uint64_t)py * scale + sy;

                if (dy >= screen->height)
                    continue;

                for (uint32_t sx = 0; sx < scale; ++sx) {
                    uint64_t dx = (uint64_t)x +
                                  (uint64_t)px * scale + sx;

                    if (dx >= screen->width)
                        continue;

                    pixel(dx, dy, color);
                }
            }
        }
    }
}

