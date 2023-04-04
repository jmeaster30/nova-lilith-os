#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <terminal/terminal.h>
#include <libk/io.h>

using namespace LibK;

extern "C" void kernel_main(void) 
{
	Kernel::Terminal::Initialize();
	
	println("Oh baby this is a really incredible test");

	auto test = "this is my string";
	formatln("print string '%s'", test);

	auto character = 'Q';
	formatln("print char '%c'", character);

	auto num = 12345;
	formatln("print int '%i'", num);

	auto bits = 12345;
	formatln("print bits '%b'", bits);
}