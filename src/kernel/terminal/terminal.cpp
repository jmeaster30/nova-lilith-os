#include "terminal.h"

namespace Terminal {

static inline uint8_t vga_entry_color(VgaColor fg, VgaColor bg) 
{
	return static_cast<uint8_t>(fg) | static_cast<uint8_t>(bg) << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) 
{
	return (uint16_t) uc | (uint16_t) color << 8;
}

size_t strlen(const char* str) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

Terminal::Terminal() {
  terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VgaColor::White, VgaColor::Black);
	terminal_buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void Terminal::SetTextColor(VgaColor color) {
  current_text_color = color;
  terminal_color = vga_entry_color(current_text_color, current_background_color);
}

void Terminal::SetBackgroundColor(VgaColor color) {
  current_background_color = color;
  terminal_color = vga_entry_color(current_text_color, current_background_color);
}

void Terminal::PutChar(char c) {
	if (c == 10) {
    if (++terminal_row == VGA_HEIGHT)
			terminal_row = 0;
    terminal_column = 0;
    return;
  }
  PutCharAt(c, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_row = 0;
	}
}

void Terminal::PutCharAt(char c, size_t x, size_t y) {
  const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, terminal_color);
}

void Terminal::Write(const char* data) {
  Write(data, strlen(data));
}

void Terminal::Write(const char* data, size_t size) {
  for (size_t i = 0; i < size; i++)
		PutChar(data[i]);
}

}