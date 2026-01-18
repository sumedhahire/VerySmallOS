#include "kernel.h"

extern char __bss[], __bss_end[], __stack_top[];

/*
"All registers except a0 & a1 must be preserved across an SBI call by the callee" means that the callee (OpenSBI side) must not change the values of except a0 and a1. In other words, from the kernel's perspective, it is guaranteed that the registers (a2 to a7) will remain the same after the call.
*/

void *memset(void *buf, char c, unsigned int n){
	unsigned int *p= (unsigned int *) buf;
	while(n--){
		*p++ = c;
	}
	return buf;
}		


struct sbiret sbi_call(long arg0,long arg1,long arg2,long arg3,long arg4, long arg5,long fid,
			long eid) {
	register long a0 __asm__("a0") = arg0;	 //preserved across all sbi call
	register long a1 __asm__("a1") = arg1;	 //preserved across all sbi call
	register long a2 __asm__("a2") = arg2;	
	register long a3 __asm__("a3") = arg3;	
	register long a4 __asm__("a4") = arg4;	
	register long a5 __asm__("a5") = arg5;	
	register long a6 __asm__("a6") = fid;	//function id for given extension id
	register long a7 __asm__("a7") = eid; //sbi extension id			
	
	__asm__ __volatile__("ecall" //controll transfer btw the supervisor(this kernel) and see (firmware of opensbi)
				: "=r"(a0), "=r"(a1) //outputs
				: "r"(a0), "r"(a1), "r"(a2), "r"(a3), "r"(a4), "r"(a5),
				 "r"(a6), "r"(a7) //rest inputs
				 :"memory");
	return (struct sbiret){.error = a0, .value = a1};
}					

void putchar(char ch) {
	sbi_call(ch, 0, 0, 0, 0, 0, 0, 1 /*Console Putchar*/);
}
/*
eid is imp
1 here means put the output in console
*/

void kernel_main(void) {
	const char *s ="\n\nHello world!\n";
	for(int i = 0; s[i] != '\0'; i++){
		putchar(s[i]); //one by one print this 
	}		
	
	for(;;){
		__asm__ __volatile__("wfi"); //let cpu sleep until after that until ctrl c
	}
}

__attribute__((section(".text.boot")))
void boot(void) {
	__asm__ __volatile__("mv sp, %0" : : "r"(__stack_top));
	memset(__bss, 0, (unsigned int)(__bss_end - __bss));
	kernel_main();
}	
		
			
				 
				 
