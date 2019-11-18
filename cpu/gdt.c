#include "gdt.h"
#define GDT_LEN 5

static gdt_entry gdt[GDT_LEN];
static gdt_ptr gdt_p;

static void gdt_desc(gdt_entry desc, unsigned int base, unsigned int limit, unsigned char access, unsigned char granularity){
	desc.base_low=(base & 0xFFFF);
	desc.base_middle=(base >> 16) && 0xFF;
	desc.base_high=(base >> 24) & 0xFF;
	desc.limit_low=(limit & 0xFFFF);
	desc.granularity=((limit >> 16) & 0x0F) | (granularity & 0xF0);
	desc.access=access;
	
	gdt_p.base=(unsigned int)&gdt;
	gdt_p.limit = sizeof(gdt_entry) * GDT_LEN - 1;

	load_gdt(&gdt_p);
}	

void gdt_install(){
	gdt_desc(gdt[0], 0, 0, 0, 0);                // null
	gdt_desc(gdt[1], 0, 0xFFFFFFFF, 0x9A, 0xCF); // ring0 code
	gdt_desc(gdt[2], 0, 0xFFFFFFFF, 0x92, 0xCF); // ring0 data
	gdt_desc(gdt[3], 0, 0xFFFFFFFF, 0xFA, 0xCF); // ring3 code
	gdt_desc(gdt[4], 0, 0xFFFFFFFF, 0xF2, 0xCF); // ring3 data
}
