#include "interrupthandler.h"

#include <libk/io.h>
#include <interrupts/pic.h>
#include <keyboard/keyboard.h>
#include <stdint.h>

namespace Kernel {
  extern "C" void InterruptHandler(int interrupt) {
    switch (interrupt) {
      case 1: {
        uint8_t scanCode = Keyboard::getscancode();
				uint8_t key = Keyboard::getkey(scanCode);
				//if printable key
				if (key != '\0' && ! (scanCode & 0x80)) {
					//put the key
					LibK::formatln("KEY PRESS: '%c'", key);
				} else {
					//handle the special key
					LibK::println("KEY PRESS: Special Character");
				}
				break;
      }
			default:
				LibK::formatln("Unhandled interrupt '%i'", interrupt);
    }
    PIC::sendeoi(interrupt);
  }
}