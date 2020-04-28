#include "debug.h"
#include "elf.h"

static void print_stack_trace();

static elf_t kernel_elf;

void init_debug()
{
	// 从 GRUB 提供的信息中获取到内核符号表和代码地址信息
	kernel_elf = elf_from_multiboot(glb_mboot_ptr);
}

void print_cur_status()
{
	static int round = 0;
	uint16_t reg1, reg2, reg3, reg4;

	asm volatile ( 	"mov %%cs, %0;"
			"mov %%ds, %1;"
			"mov %%es, %2;"
			"mov %%ss, %3;"
			: "=m"(reg1), "=m"(reg2), "=m"(reg3), "=m"(reg4));

	// 打印当前的运行级别
	printk("%d: @ring %d\n", round, reg1 & 0x3);
	printk("%d:  cs = %x\n", round, reg1);
	printk("%d:  ds = %x\n", round, reg2);
	printk("%d:  es = %x\n", round, reg3);
	printk("%d:  ss = %x\n", round, reg4);
	++round;
}

void panic(const char *msg)
{
	printk_color(rc_black, rc_red, "*** System panic! ***\n");
	printk("Message: %s\n", msg);
	printk("*** Stack trace ***\n");
	print_stack_trace();
	printk("*** GPRs ***\n");
	print_gpr_status();
	printk_color(rc_black, rc_red, "*********************\n");
	// 致命错误发生后打印栈信息后停止在这里
	while(1);
}

void print_stack_trace()
{
	uint32_t *ebp, *eip;

	asm volatile ("mov %%ebp, %0" : "=r" (ebp));
	while (ebp) {
		eip = ebp + 1;
		printk("   [0x%x] %s\n", *eip, elf_lookup_symbol(*eip, &kernel_elf));
		ebp = (uint32_t*)*ebp;
	}
}

void print_gpr_status()
{
	uint32_t eax, ebx, ecx, edx, esp, ebp, esi, edi;
	asm volatile ("mov %%eax, %0;" "mov %%ebx, %1;"
	              "mov %%ecx, %2;" "mov %%edx, %3;"
				  "mov %%esp, %4;" "mov %%ebp, %5;"
				  "mov %%esi, %6;" "mov %%edi, %7;"
				  : "=m"(eax), "=m"(ebx), 
				    "=m"(ecx), "=m"(edx), 
					"=m"(esp), "=m"(ebp), 
					"=m"(esi), "=m"(edi));
	printk("EAX = [%8xH]    EBX = [%8xH]", eax, ebx);
	printk("    ECX = [%8xH]    EDX = [%8xH]", ecx, edx);
	printk("ESP = [%8xH]    EBP = [%8xH]", esp, ebp);
	printk("    ESI = [%8xH]    EDI = [%8xH]", esi, edi);
}
