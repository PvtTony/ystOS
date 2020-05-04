#include "common.h"

//Write a byte to port
//从端口写一个字节
inline void outb(uint16_t port, uint8_t value)
{
    asm volatile("outb %1, %0" : : "dN" (port), "a" (value));
}

//Read a byte from port
//从端口读一个字节
inline uint8_t inb(uint16_t port)
{
    uint8_t ret;
    asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
    return ret;
}

//Read a word from port
//从端口读一个字
inline uint16_t inw(uint16_t port)
{
    uint16_t ret;
    asm volatile("inw %1, %0" : "=a" (ret) : "dN" (port));
    return ret;
}

//bochs magic breakpoint
void magic_bp()
{
    asm volatile("xchg %bx, %bx");
}

// 开启中断
inline void enable_intr()
{
    asm volatile ("sti");
}