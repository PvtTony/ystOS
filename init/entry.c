#include "types.h"
#include "console.h"
#include "debug.h"
#include "gdt.h"
#include "idt.h"
#include "timer.h"
#include "pmm.h"
#include "string.h"
#include "vmm.h"

/*
   System Entry 系统主入口
*/

// 打印 Logo
static void print_logo();

// 内核初始化函数
void kern_init();

// 开启分页机制之后的 Multiboot 数据指针
multiboot_t *glb_mboot_ptr;

// 开启分页机制之后的内核栈
char kern_stack[STACK_SIZE];

/* 内核使用的临时页表和页目录
 * 该地址必须是页对齐的地址，内存 0-640KB 肯定是空闲的 
 * 位于 .init.data 中
 */

// 内核使用的临时页目录
__attribute__((section(".init.data"))) pgd_t *pgd_tmp  = (pgd_t *)0x1000;
// 内核使用的临时页表 - 映射 0x00000000-0x00400000 (4MB) 的物理地址 对应原位
__attribute__((section(".init.data"))) pgd_t *pte_low  = (pgd_t *)0x2000;
// 内核使用的临时页表 - 映射 0x00000000-0x00400000 (4MB) 的物理地址到虚拟地址 0xC0000000-0xC0400000
__attribute__((section(".init.data"))) pgd_t *pte_high = (pgd_t *)0x3000;

// 内核入口函数
// 位于 .init.text
__attribute__((section(".init.text"))) void kern_entry()
{
    // 页目录映射
    pgd_tmp[0] = (uint32_t) pte_low | PAGE_PRESENT | PAGE_WRITE;
	pgd_tmp[PGD_INDEX(PAGE_OFFSET)] = (uint32_t) pte_high | PAGE_PRESENT | PAGE_WRITE;

    // 映射内核虚拟地址 4MB 到物理地址的前 4MB
	int i = 0;
	for (i = 0; i < 1024; i++) {
		pte_low[i] = (i << 12) | PAGE_PRESENT | PAGE_WRITE;
	}

    // 映射 0x00000000−0x00400000 的物理地址到虚拟地址 0xC0000000−0xC0400000
    for (i = 0; i < 1024; i++)
    {
        pte_high[i] = (i << 12) | PAGE_PRESENT | PAGE_WRITE;
    }

    // 设置临时页表
	asm volatile ("mov %0, %%cr3" : : "r" (pgd_tmp));

    // 启用分页，将 cr0 寄存器的分页位置为 1 就好
    uint32_t cr0;
	asm volatile ("mov %%cr0, %0" : "=r" (cr0));
	cr0 |= 0x80000000;
	asm volatile ("mov %0, %%cr0" : : "r" (cr0));

    // 切换内核栈
	uint32_t kern_stack_top = ((uint32_t)kern_stack + STACK_SIZE) & 0xFFFFFFF0;
	asm volatile ("mov %0, %%esp\n\t"
			    "xor %%ebp, %%ebp" : : "r" (kern_stack_top));

    // 更新全局 multiboot_t 指针
	glb_mboot_ptr = mboot_ptr_tmp + PAGE_OFFSET;

	// 调用内核初始化函数
	kern_init();
}

void kern_init()
{
    console_clear();
    print_logo();
    init_debug();
    init_gdt();
    init_idt();
    // panic("test");

    init_timer(200);
    // asm volatile ("sti");
    uint32_t start = (uint32_t) kern_start;
    uint32_t end = (uint32_t) kern_end;
    uint32_t size = (end - start + 1023) / 1024;
    printk("kernel in memory start: 0x%08X\n", start);
	printk("kernel in memory end:   0x%08X\n", end);
	printk("kernel in memory used:   %d KB\n\n", size);
	
	show_memory_map();
    init_pmm();
    init_vmm();

    printk_color(rc_black, rc_red, "\nThe Count of Physical Memory Page is: %u\n\n", phy_page_count);

	uint32_t allc_addr = NULL;
	printk_color(rc_black, rc_light_brown, "Test Physical Memory Alloc :\n");
	allc_addr = pmm_alloc_page();
	printk_color(rc_black, rc_light_brown, "Alloc Physical Addr: 0x%08X\n", allc_addr);
	allc_addr = pmm_alloc_page();
	printk_color(rc_black, rc_light_brown, "Alloc Physical Addr: 0x%08X\n", allc_addr);
	allc_addr = pmm_alloc_page();
	printk_color(rc_black, rc_light_brown, "Alloc Physical Addr: 0x%08X\n", allc_addr);
	allc_addr = pmm_alloc_page();
	printk_color(rc_black, rc_light_brown, "Alloc Physical Addr: 0x%08X\n", allc_addr);

    while (1)
    {
        asm volatile ("hlt");
    }

    // return 0;
}

/*
 * 打印 logo
 */
void print_logo()
{
    console_write("\n");
    console_write_color("##    ##  ######  ########  #######   ######  \n", rc_black, rc_green);
    console_write_color(" ##  ##  ##    ##    ##    ##     ## ##    ## \n", rc_black, rc_green);
    console_write_color("  ####   ##          ##    ##     ## ##       \n", rc_black, rc_green);
    console_write_color("   ##     ######     ##    ##     ##  ######  \n", rc_black, rc_green);
    console_write_color("   ##          ##    ##    ##     ##       ## \n", rc_black, rc_green);
    console_write_color("   ##    ##    ##    ##    ##     ## ##    ## \n", rc_black, rc_green);
    console_write_color("   ##     ######     ##     #######   ######  \n", rc_black, rc_green);
    console_write("\n");
}