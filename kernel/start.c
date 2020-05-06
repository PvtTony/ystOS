#include "uart.h"
#include "start.h"

// entry.S needs one stack per CPU.
__attribute__ ((aligned (16))) char stack0[4096];

void start()
{
    uart_init();
    uart_putc('h');
    uart_putc('e');
    uart_putc('l');
    uart_putc('l');
    uart_putc('o');
}