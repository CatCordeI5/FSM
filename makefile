CC = i686-elf-gcc
AS = nasm
LD = i686-elf-ld
CFLAGS = -m32 -ffreestanding -nostdlib -I./include
LDFLAGS = -T linker.ld --oformat binary

SRC_DIR = kernel
BOOT_DIR = boot
INCLUDE_DIR = include

OBJS = $(SRC_DIR)/kernel_main.o \
       $(SRC_DIR)/input_core.o \
       $(SRC_DIR)/loom_compiler.o \
       $(SRC_DIR)/shifthat_core.o

BOOT_OBJ = $(BOOT_DIR)/boot.o

TARGET = fsm.bin
IMAGE = fsm.img

all: $(IMAGE)

$(BOOT_OBJ): $(BOOT_DIR)/boot.asm
	$(AS) -f elf32 $< -o $@

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(BOOT_OBJ) $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

$(IMAGE): $(TARGET)
	dd if=/dev/zero of=$(IMAGE) bs=1024 count=1024
	dd if=$(TARGET) of=$(IMAGE) conv=notrunc

clean:
	rm -f $(OBJS) $(BOOT_OBJ) $(TARGET) $(IMAGE)

.PHONY: all clean
