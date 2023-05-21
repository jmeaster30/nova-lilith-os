#include "interrupthandler.h"

#include <libk/io.h>
#include <libk/abort.h>
#include <interrupts/pic.h>
#include <keyboard/keyboard.h>
#include <stdint.h>

// TODO Will need some way to allow these interrupt handlers to be dynamically settable from user space
// Section 3.4.1 from The Exokernel Operating System Architecture by Dawson R. Engler

namespace Kernel {
	extern "C" void ExceptionHandler(int interrupt) {
		LibK::formatln("EXCEPTION: %x", interrupt);
		LibK::abort();
	}

  extern "C" void InterruptHandler(int interrupt) {
    switch (interrupt) {
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
				LibK::formatln("Unhandled interrupt '%i'", interrupt);
    }
    PIC::sendeoi(interrupt);
  }
}