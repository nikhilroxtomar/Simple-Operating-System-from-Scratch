
nasm -f bin boot/boot.asm -o boot.bin

nasm -f elf32 kernel/loader.asm -o loader.o

gcc -m32 -c kernel/kernel.c -o kernel.o

ld -Ttext 0x1000 -o kernel.bin loader.o kernel.o

cat boot.bin kernel.bin > os.bin

rm *.o
qemu-system-x86_64 -kernel kernel.bin
#grub-mkrescue -o os.iso os/

