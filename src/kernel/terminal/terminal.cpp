#include "terminal.h"

namespace Kernel {

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static VgaColor current_text_color;
static VgaColor current_background_color;
static uint16_t* terminal_buffer;

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

void Terminal::Initialize() {
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
  PutCharAt(c, terminal_column, terminal_row);
}

void Terminal::PutCharAt(char c, size_t x, size_t y) {
	if (c == 8) {
		// how does backspace work at the beginning of the line
		if (terminal_column)
			terminal_column--;
    return;
  }
	if (c == 9) {
		// need to round to 4 actually
    if (terminal_column >= VGA_WIDTH - 4) {
			terminal_column = terminal_column - (VGA_WIDTH - 4);
			if (++terminal_row == VGA_HEIGHT)
				terminal_row = 0;
		} else {
			terminal_column += 4;
		}
    return;
  }
	if (c == 10) {
    if (++terminal_row == VGA_HEIGHT)
			terminal_row = 0;
    terminal_column = 0;
    return;
  }
	if (c == 13) {
    terminal_column = 0;
    return;
  }
  const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, terminal_color);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT) // TODO make this scroll
			terminal_row = 0;
	}
}

void Terminal::Write(const char* data) {
  Write(data, strlen(data));
}

void Terminal::Write(const char* data, size_t size) {
  for (size_t i = 0; i < size; i++)
		PutChar(data[i]);
}

}