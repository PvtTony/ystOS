#include "memlayout.h"
#include "uart.h"

// the UART control registers are memory-mapped
// at address UART0. this macro returns the
// address of one of the registers.
#define Reg(reg) ((volatile unsigned char *)(UART0 + reg))

// the UART control registers.
// some have different meanings for
// read vs write.
// http://byterunner.com/16550.html
#define RHR 0 // receive holding register (for input bytes)
#define THR 0 // transmit holding register (for output bytes)
#define IER 1 // interrupt enable register
#define FCR 2 // FIFO control register
#define ISR 2 // interrupt status register
#define LCR 3 // line control register
#define LSR 5 // line status register

#define ReadReg(reg) (*(Reg(reg)))
#define WriteReg(reg, v) (*(Reg(reg)) = (v))

// 初始化 UART
void uart_init()
{
    // disable interrupts.
  WriteReg(IER, 0x00);
  // special mode to set baud rate.
  WriteReg(LCR, 0x80);

  // LSB for baud rate of 38.4K.
  WriteReg(0, 0x03);

  // MSB for baud rate of 38.4K.
  WriteReg(1, 0x00);

  // leave set-baud mode,
  // and set word length to 8 bits, no parity.
  WriteReg(LCR, 0x03);

  // reset and enable FIFOs.
  WriteReg(FCR, 0x07);

  // enable receive interrupts.
  WriteReg(IER, 0x01);
}

void uart_putc(int c)
{
    while ((ReadReg(LSR)& (1 << 5)) == 0);
    WriteReg(THR, c);
}