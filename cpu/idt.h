#ifndef __IDT_H__
#define __IDT_H__

#define low_16(address) (unsigned short)((address) & 0xFFFF)
#define high_16(address) (unsigned short)(((address) >> 16) & 0xFFFF)

#define KERNEL_CS 0x08
#define IDT_FLAGS 0x8E

struct idt_entry{
	unsigned short low_offset;
	unsigned short sel;
	unsigned char zero;
	unsigned char flags;
	unsigned short high_offset;
}__attribute__((packed));

struct idt_ptr{
	unsigned short limit;
	unsigned long base;
}__attribute__((packed));

void idt_desc(int n, unsigned long base);
void set_idt();

#endif
