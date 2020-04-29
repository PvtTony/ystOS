#include "types.h"
#include "console.h"
#include "debug.h"
#include "gdt.h"
#include "idt.h"

/*
##    ##  ######  ########  #######   ######  
 ##  ##  ##    ##    ##    ##     ## ##    ## 
  ####   ##          ##    ##     ## ##       
   ##     ######     ##    ##     ##  ######  
   ##          ##    ##    ##     ##       ## 
   ##    ##    ##    ##    ##     ## ##    ## 
   ##     ######     ##     #######   ######  

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
    
    asm volatile ("int $0x3"); 
    asm volatile ("int $0x4");
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