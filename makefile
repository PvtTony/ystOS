#!Makefile

# patsubst 处理所有在 C_SOURCES 字列中的字（一列文件名），如果它的 结尾是 '.c'，就用 '.o' 把 '.c' 取代
C_SOURCES = $(shell find . -name "*.c")
C_OBJECTS = $(patsubst %.c, %.o, $(C_SOURCES))
S_SOURCES = $(shell find . -name "*.s")
S_OBJECTS = $(patsubst %.s, %.o, $(S_SOURCES))

CC = gcc
LD = ld
ASM = nasm

C_FLAGS = -c -g -Wall -m32 -ggdb -gstabs+ -nostdinc -fno-builtin -fno-stack-protector -I include
LD_FLAGS = -T scripts/kernel.ld -m elf_i386 -nostdlib
ASM_FLAGS = -f elf -g -F stabs
QEMU_FLAGS = -cpu pentium -fda floppy.img -boot a 
QEMU_DEBUG_FLAGS = $(QEMU_FLAGS) -S -s & 

all: $(S_OBJECTS) $(C_OBJECTS) link update_image
         
# The automatic variable `$<' is just the first prerequisite
.c.o:
	@echo Compiling Code file $< ...
	$(CC) $(C_FLAGS) $< -o $@

.s.o:
	@echo Compiling Asm file $< ...
	$(ASM) $(ASM_FLAGS) $<

link:
	@echo Compiling Core file...
	$(LD) $(LD_FLAGS) $(S_OBJECTS) $(C_OBJECTS) -o yst_kernel

.PHONY:clean
clean:
	$(RM) $(S_OBJECTS) $(C_OBJECTS) yst_kernel

.PHONY:update_image
update_image:
	sudo mount floppy.img /mnt/kernel
	sudo cp yst_kernel /mnt/kernel/yst_kernel
	sleep 1
	sudo umount /mnt/kernel

.PHONY:mount_image
mount_image:
	sudo mount floppy.img /mnt/kernel

.PHONY:umount_image
umonut_image:
	sudo umount /mnt/kernel

.PHONY:qemu
qemu:
	qemu-system-i386 $(QEMU_FLAGS)
	
.PHONY:bochs
bochs:
	bochs -q -f ./.bochsrc

.PHONY:debug
debug:
	qemu-system-i386 $(QEMU_DEBUG_FLAGS)
	sleep 1
	cgdb -x scripts/gdbinit
.PHONY:debug_gui
debug_gui:
	qemu-system-i386 $(QEMU_DEBUG_FLAGS)
	sleep 1
	kdbg -r localhost:1234 yst_kernel 