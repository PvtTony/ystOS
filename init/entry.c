#include "types.h"
#include "console.h"
#include "debug.h"
#include "gdt.h"
#include "idt.h"
#include "timer.h"
#include "pmm.h"
#include "string.h"

/*
   System Entry
*/

static void print_logo();

int kern_entry()
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



    return 0;
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