wor to compil:
1.nasm -f elf32 boot.asm -o boot.o
2.gcc -c kernel.c -o kernel.o -m32 -ffreestanding -nostdlib
3.ld -m elf_i386 -T linker.ld -o fsm.bin boot.o kernel.o --oformat binary
4.make 1 megabyte empty file image:
dd if=/dev/zero of=fsm.img bs=1024 count=1024
5.merge the bootloader and kernel to the image:
dd if=fsm.bin of=fsm.img conv=notrunc
