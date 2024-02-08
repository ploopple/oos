#include "tty.h"
#include "vga.h"

void kernel_main(void) {
  clear_screen(VGA_COLOR_GREEN, VGA_COLOR_BLACK);
  enable_cursor(0, 120);
  print("hi there\n whats\nup there sdfdf"); 
  set_output_color(VGA_COLOR_RED, VGA_COLOR_LIGHT_GREEN);
  print("hi there\n whats\nup there sdfdf"); 
  while (1);
}