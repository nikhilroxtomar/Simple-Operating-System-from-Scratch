#include "kb.h"
#include "irq.h"

void keyboard_handler(struct regs r){

}

void keyboard_install(){
	irq_install_handlers(IRQ1, keyboard_handler);
}
