; -------------------------
; 加载 GDT Description 到 GDTR 中
; LGDT 指令
; -------------------------

[global gdt_flush]
gdt_flush:
    mov eax, [esp + 4] ; 参数存入 eax 
    lgdt [eax] ; 加载到 GDTR [修改原先GRUB设置]

    mov ax, 0x10 ; 加载我们的数据段描述符
    mov ds, ax ; 更新所有可以更新的段寄存器
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:_flush ; 远跳转，0x08是代码段描述符
                    ; 目的是清空流水线并串行化处理器

_flush:
    ret