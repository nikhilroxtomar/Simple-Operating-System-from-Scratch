[bits 16]
[org 0x7c00]

global _start

_start:
	mov ax, 0
	mov ss, ax
	mov bp, 0x9000
	mov sp, bp

	jmp 0:loader

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
	dw gdt_end-gdt_start-1
	dd gdt_start

CODE_SEG equ gdt_code-gdt_start
DATA_SEG equ gdt_data-gdt_start

print:
	pusha
	mov ah, 0x0e
repeat:
	mov al, [bx]
	cmp al, 0
	je done
	int 0x10
	add bx, 1
	jmp repeat
done:
	popa
	ret

MSG db "welcome to bootloader",13,10,0
PROT db "loading protected mode",13,10,0
ERR db "Error in reading disk",13,10,0

error:
	mov bx, ERR
	call print	
	jmp disk_loop
disk_loop:
	jmp $

loader:
	mov ax, 0
    	mov ds, ax
   	mov es, ax
  	mov fs, ax
  	mov gs, ax
	
	mov ah, 0x06
	mov al, 0
	int 0x10
	mov ah, 0x00
	mov al, 7h
	int 0x10

	mov bx, MSG
	call print
	
	mov bx, 0x1000	

	mov ah, 0x2
	mov al, 0x2
	mov cl, 0x2
	mov ch, 0x0
	mov dh, 0x0
	int 0x13
	jc error
	jnc switch_pm
	
switch_pm:
	xor ax, ax
	mov ds, ax
	cli
	lgdt[gdt_desc]
	mov eax, cr0
	or eax, 0x1
	mov cr0, eax
	jmp CODE_SEG:init_pm

[bits 32]

VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f

print_pm:
    pusha
    mov edx, VIDEO_MEMORY
loop_pm:
    mov al, [ebx]
    mov ah, WHITE_ON_BLACK
    cmp al, 0
    je done_pm
    mov [edx], ax
    add ebx, 1
    add edx, 2
    jmp loop_pm
done_pm:
    popa
    ret

init_pm:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    mov ebp, 0x9000
    mov esp, ebp

    mov ebx, PROT
    call print_pm

    jmp $

times 510-($-$$) db 0
dw 0xAA55
