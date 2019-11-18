#include "idt.h"

struct idt_entry idt[256];
struct idt_ptr idt_p;

void idt_desc(int n, unsigned long base){
	idt[n].low_offset=low_16(base);
	idt[n].sel=KERNEL_CS;
	idt[n].zero=0;
	idt[n].flags=IDT_FLAGS;
	idt[n].high_offset=high_16(base);
} 

void set_idt(){
	idt_p.limit=(sizeof(struct idt_entry)*256)-1;
	idt_p.base=(unsigned long)&idt;
	load_idt(&idt_p);
};
