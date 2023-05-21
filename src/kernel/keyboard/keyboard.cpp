#include "keyboard.h"

#include <libk/asm.h>

static const char keySet1[ ] =
{
	//'\0' /*unused*/, '\0' /*L GUI*/, '\0' /*R CTRL*/, '\0' /*R GUI*/, '\0' /*R ALT*/, '\0' /*APPS*/, '\0' /*PRNT SCRN*/, '\0' /*PAUSE*/, '\0' /*INSERT*/, '\0' /*HOME*/, '\0' /*PG UP*/, '\0' /*DELETE*/, '\0' /*END*/, '\0' /*PG DN*/, '\0' /*U ARROW*/, '\0' /*L ARROW*/, '\0' /*D ARROW*/, '\0' /*R ARROW*/, '\0' /*KP /*/, '\0' /*KP EN*/, /*multi scancode, not in correct place in array*/
	'\0'/*unused*/, '\0' /*ESC*/, '1', '2', '3', '4', '5', '6', '7',
	'8', '9', '0', '-', '=', '\b' /*BKSP*/, '\t' /*TAB*/, 'q', 'w',
	'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']',
	'\n' /*ENTER*/, '\0' /*L CTRL*/, 'a', 's', 'd', 'f', 'g', 'h',
	'j', 'k', 'l', ';', '\'', '`', '\0' /*L SHFT*/, '\\', 'z', 'x',
	'c', 'v', 'b', 'n', 'm', ',', '.', '/', '\0' /*R SHFT*/,
	'\0' /*KP **/, '\0' /*L ALT*/, ' ' /*SPACE*/, '\0' /*CAPS*/,
	'\0' /*F1*/, '\0' /*F2*/, '\0' /*F3*/, '\0' /*F4*/, '\0' /*F5*/,
	'\0' /*F6*/, '\0' /*F7*/, '\0' /*F8*/, '\0' /*F9*/,
	'\0' /*F10*/, '\0' /*NUM*/, '\0' /*SCROLL*/, '\0' /*KP 7*/,
	'\0' /*KP 8*/, '\0' /*KP 9*/, '\0' /*KP -*/, '\0' /*KP 4*/,
	'\0' /*KP 5*/, '\0' /*KP 6*/, '\0' /*KP +*/, '\0' /*KP 1*/,
	'\0' /*KP 2*/, '\0' /*KP 3*/, '\0' /*KP 0*/, '\0' /*KP .*/,
	'\0' /*unused*/, '\0' /*unused*/, '\0' /*unused*/, '\0' /*F11*/,
	'\0' /*F12*/, };
/**
 * table containing all possible keys, with a case mod key
 */
static const char keySet1Upper[ ] =
{
	//'\0' /*unused*/, '\0' /*L GUI*/, '\0' /*R CTRL*/, '\0' /*R GUI*/, '\0' /*R ALT*/, '\0' /*APPS*/, '\0' /*PRNT SCRN*/, '\0' /*PAUSE*/, '\0' /*INSERT*/, '\0' /*HOME*/, '\0' /*PG UP*/, '\0' /*DELETE*/, '\0' /*END*/, '\0' /*PG DN*/, '\0' /*U ARROW*/, '\0' /*L ARROW*/, '\0' /*D ARROW*/, '\0' /*R ARROW*/, '\0' /*KP /*/, '\0' /*KP EN*/, /*multi scancode, not in correct place in array*/
	'\0'/*unused*/, '\0' /*ESC*/, '!', '@', '#', '$', '%', '^', '&',
	'*', '(', ')', '_', '+', '\0' /*BKSP*/, '\0' /*TAB*/, 'Q', 'W',
	'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}',
	'\0' /*ENTER*/, '\0' /*L CTRL*/, 'A', 'S', 'D', 'F', 'G', 'H',
	'J', 'K', 'L', ':', '"', '~', '\0' /*L SHFT*/, '|', 'Z', 'X',
	'C', 'V', 'B', 'N', 'M', '<', '>', '?', '\0' /*R SHFT*/,
	'\0' /*KP **/, '\0' /*L ALT*/, ' ' /*SPACE*/, '\0' /*CAPS*/,
	'\0' /*F1*/, '\0' /*F2*/, '\0' /*F3*/, '\0' /*F4*/, '\0' /*F5*/,
	'\0' /*F6*/, '\0' /*F7*/, '\0' /*F8*/, '\0' /*F9*/,
	'\0' /*F10*/, '\0' /*NUM*/, '\0' /*SCROLL*/, '\0' /*KP 7*/,
	'\0' /*KP 8*/, '\0' /*KP 9*/, '\0' /*KP -*/, '\0' /*KP 4*/,
	'\0' /*KP 5*/, '\0' /*KP 6*/, '\0' /*KP +*/, '\0' /*KP 1*/,
	'\0' /*KP 2*/, '\0' /*KP 3*/, '\0' /*KP 0*/, '\0' /*KP .*/,
	'\0' /*unused*/, '\0' /*unused*/, '\0' /*unused*/, '\0' /*F11*/,
	'\0' /*F12*/, };

namespace Kernel {
  uint8_t Keyboard::getscancode() {
    uint8_t scancode = 0;
    scancode = LibK::inb(Keyboard::port);
    return scancode;
  }

  uint8_t Keyboard::getkey() {
    return getkey(0);
  }

  uint8_t Keyboard::getkey(uint16_t modkeys) {
    return getkey(getscancode(), modkeys);
  }

  uint8_t Keyboard::getkey(uint8_t scancode, uint16_t modkeys) {
    if ((modkeys & (L_SHIFT | R_SHIFT | CAPS_LOCK)) != 0) {
      return keySet1Upper[scancode];
    }
    return keySet1[scancode];
  }
}