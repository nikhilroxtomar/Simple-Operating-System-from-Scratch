C_SOURCES = $(wildcard kernel/*.c include/*.c cpu/*.c)
HEADERS = $(wildcard kernel/*.h include/*.h cpu/*.h)


loader:
	nasm -f elf32 -o loader.o kernel/loader.asm
	nasm -f elf32 -o cpu/interrupt.o cpu/interrupt.asm

kern:
	gcc -m32 -g -ffreestanding -c include/print.c -o include/print.o
	gcc -m32 -g -ffreestanding -c include/ports.c -o include/ports.o
	gcc -m32 -g -ffreestanding -c include/string.c -o include/string.o
	gcc -m32 -g -ffreestanding -c cpu/idt.c -o cpu/idt.o
	gcc -m32 -g -ffreestanding -c cpu/irq.c -o cpu/irq.o
	gcc -m32 -g -ffreestanding -c cpu/timer.c -o cpu/timer.o
	gcc -m32 -g -ffreestanding -c cpu/kb.c -o cpu/kb.o
	gcc -m32 -g -ffreestanding -c user/shell/shell.c -o user/shell/shell.o
	gcc -m32 -g -ffreestanding -c user/taskbar/taskbar.c -o user/taskbar/taskbar.o
	gcc -m32 -g -ffreestanding -c kernel/kernel.c -o main.o

link:
	ld -m elf_i386 -Ttext 0x1000 -o kernel.bin loader.o main.o $(wildcard include/*.o cpu/*.o user/shell/*.o user/taskbar/*.o)

run:
	qemu-system-x86_64 -kernel kernel.bin
clean:
	rm *.o include/*.o cpu/*.o user/shell/*.o user/taskbar/*.o

all:loader kern link clean run
