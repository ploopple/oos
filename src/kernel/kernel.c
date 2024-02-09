#include "tty.h"
#include "vga.h"

void kernel_main(void) {
  clear_screen(VGA_COLOR_GREEN, VGA_COLOR_BLACK);
  enable_cursor(0, 120);
  set_output_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
  print("Welcome to my OS\nThis is a simple message to test :)"); 
  while (1);
}
