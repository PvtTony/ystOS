#ifndef INCLUDE_UART_H_
#define INCLUDE_UART_H_

// 初始化 UART
void uart_init();

// trap.c calls here when the uart interrupts.
void uart_intr(void);

// write one output character to the UART.
void uart_putc(int);

// read one input character from the UART.
// return -1 if none is waiting.
int uart_getc(void);

#endif // INCLUDE_UART_H_