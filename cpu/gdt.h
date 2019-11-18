#ifndef __GDT_H__
#define __GDT_H__

typedef struct{
	unsigned short limit_low;
	unsigned short base_low;
	unsigned char base_middle;
	unsigned char access;
	unsigned char granularity;
	unsigned char base_high;
}__attribute__((packed)) gdt_entry;

typedef struct{
	unsigned short limit;
	unsigned int base;
}__attribute__((packed)) gdt_ptr;

#endif
