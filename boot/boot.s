;------------------------------------------------
;
; boot.s Kernel Starts from here
;
;------------------------------------------------

;Multiboot Header MagicNumber --> 由规范决定
MBOOT_HEADER_MAGIC  equ    0x1BADB002

;0号位表示所有的引导模块将按页（4KB)对齐
MBOOT_PAGE_ALIGN    equ    1 << 0

;1号位通过Multiboot 信息结构的mem_× 域包括可用内存的信息
;告诉 (把内存空间的信息包含在信息结构中GrubMultiboot
MBOOT_MEM_INFO      equ    1 << 1

;Declare the Multiboot label we used
MBOOT_HEADER_FLAGS  equ    MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO

MBOOT_CHECKSUM      equ    -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)

[BITS 32]
section .text

dd MBOOT_HEADER_MAGIC
dd MBOOT_HEADER_FLAGS
dd MBOOT_CHECKSUM

[GLOBAL start]
[GLOBAL glb_mboot_ptr]
[EXTERN kern_entry]

start:
    cli

    mov esp, STACK_TOP
    mov ebp, 0
    and esp, 0FFFFFF0H
    mov [glb_mboot_ptr], ebx
    call kern_entry
stop:
    hlt
    jmp stop

;------------------------------------------------

section .bss
stack:
    resb 32768
glb_mboot_ptr:
    resb 4

STACK_TOP equ $-stack-1