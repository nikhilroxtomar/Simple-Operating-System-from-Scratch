#include "timer.h"
#include "../include/print.h"
#include "../include/ports.h"
#include "../cpu/irq.h"

unsigned int tick=0;

void timer_handler(struct regs r){
	tick++;
	unsigned int s=0;
	if(tick%18==0){
	print_num(s++);
	print(" has passed\n");		
	}	
}

void timer_install(){
	irq_install_handlers(IRQ0, timer_handler);
}

void init_timer(unsigned int freq){
	irq_install();
	unsigned int divisor=1193180/freq;
	unsigned char low=(unsigned char)(divisor & 0XFF);
	unsigned char high=(unsigned char)((divisor >> 8) & 0XFF);
	
	outb(0X43, 0X36);
	outb(0X40, low);
	outb(0X40, high);
}
