#include "interrupthandler.h"

#include <libk/io.h>
#include <libk/abort.h>
#include <interrupts/pic.h>
#include <keyboard/keyboard.h>
#include <stdint.h>

// TODO Will need some way to allow these interrupt handlers to be dynamically settable from user space
// Section 3.4.1 from The Exokernel Operating System Architecture by Dawson R. Engler

const char *exception_messages[] = {
	"Division By Zero",
	"Debug Exception",
	"Non-Maskable Interrupt Exception",
	"Breakpoint Exception",
	"Into Detected Overflow Exception",
	"Out of Bounds Exception",
	"Invalid Opcode Exception",
	"No Coprocessor Exception",
	"Double Fault Exception",
	"Coprocessor Segment Overrun Exception",
	"Bad TSS Exception",
	"Segment No Present Exception",
	"Stack Fault Exception",
	"General Protection Fault Exception",
	"Page Fault Exception",
	"Unknown Interrupt Exception",
	"Coprocessor Fault Exception",
	"Alignment Check Exception (486+)",
	"Machine Check Exception (Pentium/586+)",
	"Reserved Exception",
	"Reserved Exception",
	"Reserved Exception",
	"Reserved Exception",
	"Reserved Exception",
	"Reserved Exception",
	"Reserved Exception",
	"Reserved Exception",
	"Reserved Exception",
	"Reserved Exception",
	"Reserved Exception",
	"Reserved Exception",
	"Reserved Exception",
};

namespace Kernel {
	void dump_register_info(const struct Registers *registers) {
		LibK::formatln("Interrupt   %x  Error Code  %x", registers->int_no, registers->err_code);
		LibK::formatln("EFlags      %x  UseResp     %x", registers->eflags, registers->useresp);
		LibK::formatln("DS  %x  ES  %x  FS  %x  GS  %x", registers->ds, registers->es, registers->fs, registers->gs);
		LibK::formatln("EAX %x  EBX %x  ECX %x  EDX %x", registers->eax, registers->ebx, registers->ecx, registers->edx);
		LibK::formatln("EDI %x  ESI %x  EBP %x  ESP %x", registers->edi, registers->esi, registers->ebp, registers->esp);
		LibK::formatln("EIP %x  CS  %x  SS  %x", registers->eip, registers->cs, registers->ss);
	}

	extern "C" void ExceptionHandler(const struct Registers *registers) {
		const char * message = registers->int_no < 32 ? exception_messages[registers->int_no] : "Unknown Exception :(";
		LibK::formatln("\nEXCEPTION %x '%s'", registers->int_no, message);
		dump_register_info(registers);
		LibK::abort();
	}

  extern "C" void InterruptHandler(const struct Registers *registers) {
		LibK::println("Starting Interrupt Handler");
		dump_register_info(registers);
    switch (registers->int_no) {
			case 0: {
				LibK::print("timer");
				break;
			}
      case 1: {
        uint8_t scanCode = Keyboard::getscancode();
				uint8_t key = Keyboard::getkey(scanCode, 0);
				//if printable key
				if (key != '\0' && ! (scanCode & 0x80)) {
					//put the key
					LibK::format("%c", key);
				} else {
					//handle the special key
					//LibK::formatln("KEY PRESS Special Character 0x%x", scanCode);
				}
				break;
      }
			default:
				LibK::formatln("Unhandled interrupt '%i'", registers->int_no);
    }
    PIC::sendeoi(registers->int_no);
		LibK::println("\nExiting Interrupt Handler");
  }
}