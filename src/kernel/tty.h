#pragma once

#include "vga.h"

extern uint32_t cursorX;
extern uint32_t cursorY;
extern enum vga_color FG;
extern enum vga_color BG;

void clear_screen(enum vga_color fg, enum vga_color bg);
void enable_cursor(uint8_t cursor_start, uint8_t cursor_end);
void update_cursor(int x, int y);
void write_char(const char c); 
void print(const char *str);
void set_output_color(enum vga_color fg, enum vga_color bg);
