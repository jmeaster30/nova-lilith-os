#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <terminal/terminal.h>
#include <structures/descriptortable.h>
#include <interrupts/interrupttable.h>
#include <libk/io.h>
#include <libk/asm.h>

using namespace LibK;

Kernel::GlobalDescriptorTable GlobalDescriptorTable;
Kernel::InterruptDescriptorTable InterruptDescriptorTable;

extern "C" void kernel_init(void)
{
	LibK::deactivate_interrupts();

	Kernel::Terminal::Initialize();
	GlobalDescriptorTable.Initialize();
	InterruptDescriptorTable.Initialize();

	LibK::activate_interrupts();

	println("Finished Kernel Setup");	
}

extern "C" void kernel_main(void) 
{

	/*
	println("Oh baby this is a really incredible test");

	auto test = "this is my string";
	formatln("print string '%s'", test);

	auto character = 'Q';
	formatln("print char '%c'", character);

	auto num = 12345;
	formatln("print int '%i'", num);

	auto bits = 12345;
	formatln("print bits '%b'", bits);

	auto hex = 0xdeadbeef;
	formatln("print hex '%x'", hex);
	formatln("print int '%i'", hex);
	*/

	int i = 0;
	char c = '|';
	while (true) {
		i++;
		if (i == 4) {
			i = 0;
		}
		if (i == 0) {
			c = '|';
		} else if (i == 1) {
			c = '/';
		} else if (i == 2) {
			c = '-';
		} else if (i == 3) {
			c = '\\';
		}
		format("\r%c", c);
		//asm("hlt");
	}
}