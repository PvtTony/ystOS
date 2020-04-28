#include "types.h"
#include "console.h"
#include "debug.h"
#include "gdt.h"

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
    panic("test");
    
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