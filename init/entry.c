#include "types.h"
#include "console.h"

int kern_entry()
{
    console_clear();
/*
##    ##  ######  ########  #######   ######  
 ##  ##  ##    ##    ##    ##     ## ##    ## 
  ####   ##          ##    ##     ## ##       
   ##     ######     ##    ##     ##  ######  
   ##          ##    ##    ##     ##       ## 
   ##    ##    ##    ##    ##     ## ##    ## 
   ##     ######     ##     #######   ######  
*/
    console_write_color("Hello, ystOS Kernel!\n", rc_black, rc_red);
    console_write_color("Hello, ystOS Kernel!\n", rc_black, rc_blue);
    console_write_color("Hello, ystOS Kernel!\n", rc_black, rc_green);
    console_write("\n");
    console_write_color("##    ##  ######  ########  #######   ######  \n", rc_black, rc_cyan);
    console_write_color(" ##  ##  ##    ##    ##    ##     ## ##    ## \n", rc_black, rc_cyan);
    console_write_color("  ####   ##          ##    ##     ## ##       \n", rc_black, rc_cyan);
    console_write_color("   ##     ######     ##    ##     ##  ######  \n", rc_black, rc_cyan);
    console_write_color("   ##          ##    ##    ##     ##       ## \n", rc_black, rc_cyan);
    console_write_color("   ##    ##    ##    ##    ##     ## ##    ## \n", rc_black, rc_cyan);
    console_write_color("   ##     ######     ##     #######   ######  \n", rc_black, rc_cyan);


    return 0;
}