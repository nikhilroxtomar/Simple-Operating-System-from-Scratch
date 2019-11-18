[bits 32]
section .text
	align 4
	dd 0x1BADB002
	dd 0x0
	dd -(0x1BADB002+0x0)

[extern main]
global _start	
global load_idt

_start:
	mov ebp, 0x90000
	mov esp, ebp
	jmp kernel

gdt_start: 
    dd 0x0 
    dd 0x0

gdt_code: 
    dw 0xffff    
    dw 0x0       
    db 0x0       
    db 10011010b 
    db 11001111b 
    db 0x0       

gdt_data:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10010010b
    db 11001111b
    db 0x0

gdt_end:

gdt_desc:
    dw gdt_end - gdt_start - 1 
    dd gdt_start

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

load_idt:
	mov eax, [esp+4]
	lidt[eax]
	ret

kernel:
	lgdt[gdt_desc];
	mov eax, cr0
	or eax, 0x1
	mov cr0, eax
	cli
	call main	
	hlt
