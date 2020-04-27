#include "types.h"
#include "console.h"
#include "debug.h"

/*
##    ##  ######  ########  #######   ######  
 ##  ##  ##    ##    ##    ##     ## ##    ## 
  ####   ##          ##    ##     ## ##       
   ##     ######     ##    ##     ##  ######  
   ##          ##    ##    ##     ##       ## 
   ##    ##    ##    ##    ##     ## ##    ## 
   ##     ######     ##     #######   ######  
*/

int kern_entry()
{
    console_clear();
    init_debug();
    console_write_color("Hello, ystOS Kernel!\n", rc_black, rc_green);
    console_write("\n");
    console_write_color("##    ##  ######  ########  #######   ######  \n", rc_black, rc_cyan);
    console_write_color(" ##  ##  ##    ##    ##    ##     ## ##    ## \n", rc_black, rc_cyan);
    console_write_color("  ####   ##          ##    ##     ## ##       \n", rc_black, rc_cyan);
    console_write_color("   ##     ######     ##    ##     ##  ######  \n", rc_black, rc_cyan);
    console_write_color("   ##          ##    ##    ##     ##       ## \n", rc_black, rc_cyan);
    console_write_color("   ##    ##    ##    ##    ##     ## ##    ## \n", rc_black, rc_cyan);
    console_write_color("   ##     ######     ##     #######   ######  \n", rc_black, rc_cyan);
    panic("test");
    
    return 0;
}