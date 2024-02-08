
#include "tty.h"
#include "port.h"
#include "vga.h"
#include <stdint.h>


uint32_t cursorX = 0;
uint32_t cursorY = 0;
enum vga_color FG = VGA_COLOR_GREEN;
enum vga_color BG = VGA_COLOR_WHITE;


void clear_screen(enum vga_color fg, enum vga_color bg) {
  uint8_t color = vga_entry_color(fg, bg);
  for (uint16_t i = 0; i < (160 * 25); i++) {
    vga[i] = vga_entry(' ', color);
  }
}

void enable_cursor(uint8_t cursor_start, uint8_t cursor_end) {
  outb(0x3D4, 0x0A);
  outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);
  outb(0x3D4, 0x0B);
  outb(0x3D5, (inb(0x3D5) & 0xE0) | cursor_end);
  update_cursor(0, 0);
}

void update_cursor(int x, int y) {
  uint16_t pos = y * 80 + x;

  outb(0x3D4, 14);
  outb(0x3D5, pos >> 8);
  outb(0x3D4, 15);
  outb(0x3D5, pos);
}

void write_char(const char c) {
  uint16_t i = (cursorY * 80) + cursorX;
  if (c == '\n') {
    cursorY++;
    i = (cursorY * 80) + cursorX;
    cursorX = 0;
  } else {
    uint8_t color = vga_entry_color(FG, BG);
    vga[i] = vga_entry(c, color);
    cursorX++;
    i++;
  }
  update_cursor(cursorX, cursorY);
}

void print(const char *str) {
  for(uint32_t i = 0; str[i] != '\0';i++) {
    write_char(str[i]);
  }
}

void set_output_color(enum vga_color fg, enum vga_color bg) {
  FG = fg;
  BG = bg;
}
