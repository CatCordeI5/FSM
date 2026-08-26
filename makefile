CC = gcc
AS = nasm
LD = ld
CFLAGS = -m32 -ffreestanding -nostdlib -fno-pie -no-pie
LDFLAGS = -T linker.ld --oformat binary -m elf_i386

OBJS = input_core.o \
       kernel_main.o \
       loom_compiler.o \
       shifthat_core.o

BOOT_OBJ = boot.o

TARGET = fsm.bin
IMAGE = fsm.img

all: $(IMAGE)

$(BOOT_OBJ): boot.asm
	$(AS) -f elf32 $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(BOOT_OBJ) $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

$(IMAGE): $(TARGET)
	dd if=/dev/zero of=$(IMAGE) bs=1024 count=1024
	dd if=$(TARGET) of=$(IMAGE) conv=notrunc

clean:
	rm -f *.o $(TARGET) $(IMAGE)

.PHONY: all clean
