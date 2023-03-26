#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "terminal/terminal.h"
 
extern "C" void kernel_main(void) 
{
	auto term = Terminal::Terminal();
	term.SetTextColor(Terminal::VgaColor::Red);
	term.Write("THIS IS MY OPERATING SYSTEM\n");
}