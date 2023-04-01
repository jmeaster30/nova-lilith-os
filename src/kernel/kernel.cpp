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

	int num = 12345;
	auto color = Kernel::VgaColor::Red;
	formatln("{color} LOOK AT THIS {color:reset} My Num: {color:blue}{}{color:reset}", color, num);
}