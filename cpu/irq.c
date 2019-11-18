#include "irq.h"
#include "idt.h"
#include "../include/print.h"
#include "../include/ports.h"
#include "../include/string.h"

void irq_install(){
	idt_desc(0, (unsigned int)isr0);
	idt_desc(1, (unsigned int)isr1);
	idt_desc(2, (unsigned int)isr2);
	idt_desc(3, (unsigned int)isr3);
	idt_desc(4, (unsigned int)isr4);
	idt_desc(5, (unsigned int)isr5);
	idt_desc(6, (unsigned int)isr6);
	idt_desc(7, (unsigned int)isr7);
	idt_desc(8, (unsigned int)isr8);
	idt_desc(9, (unsigned int)isr9);
	idt_desc(10, (unsigned int)isr10);
	idt_desc(11, (unsigned int)isr11);
	idt_desc(12, (unsigned int)isr12);
	idt_desc(13, (unsigned int)isr13);
	idt_desc(14, (unsigned int)isr14);
	idt_desc(15, (unsigned int)isr15);
	idt_desc(16, (unsigned int)isr16);
	idt_desc(17, (unsigned int)isr17);
	idt_desc(18, (unsigned int)isr18);
	idt_desc(19, (unsigned int)isr19);
	idt_desc(20, (unsigned int)isr20);
	idt_desc(21, (unsigned int)isr21);
	idt_desc(22, (unsigned int)isr22);
	idt_desc(23, (unsigned int)isr23);
	idt_desc(24, (unsigned int)isr24);
	idt_desc(25, (unsigned int)isr25);
	idt_desc(26, (unsigned int)isr26);
	idt_desc(27, (unsigned int)isr27);
	idt_desc(28, (unsigned int)isr28);
	idt_desc(29, (unsigned int)isr29);
	idt_desc(30, (unsigned int)isr30);
	idt_desc(31, (unsigned int)isr31);

    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0); 

    idt_desc(32, (unsigned int)irq0);
    idt_desc(33, (unsigned int)irq1);
    idt_desc(34, (unsigned int)irq2);
    idt_desc(35, (unsigned int)irq3);
    idt_desc(36, (unsigned int)irq4);
    idt_desc(37, (unsigned int)irq5);
    idt_desc(38, (unsigned int)irq6);
    idt_desc(39, (unsigned int)irq7);
    idt_desc(40, (unsigned int)irq8);
    idt_desc(41, (unsigned int)irq9);
    idt_desc(42, (unsigned int)irq10);
    idt_desc(43, (unsigned int)irq11);
    idt_desc(44, (unsigned int)irq12);
    idt_desc(45, (unsigned int)irq13);
    idt_desc(46, (unsigned int)irq14);
    idt_desc(47, (unsigned int)irq15);

	set_idt();
}

char* exception[]={
	"Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"

};

isr_t interrupt_handlers[256];

void isr_handler(struct regs r){ 
	print("\nInterrupt Encountered: ");
	char s[3];
	int_to_ascii(r.int_no, s);
	print(s);
	print("\n");
	print(exception[r.int_no]);
	print("\n");
}

void irq_install_handlers(unsigned char n, isr_t handler) {
    interrupt_handlers[n] = handler;
}

void irq_handler(struct regs r){

	if (r.int_no >= 40) outb(0xA0, 0x20);
    outb(0x20, 0x20);
	if (interrupt_handlers[r.int_no] != 0) {
        isr_t handler = interrupt_handlers[r.int_no];
       handler(r);
    }
}


