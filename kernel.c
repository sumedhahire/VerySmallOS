typedef unsigned char uint8_t; //alias
typedef unsigned int uint32_t; //alias
typedef uint32_t size_t; //use for something

//extern means this symbol is external somewhere 
extern char __bss[], __bss_end[], __stack_top[];

//buffer c and size n
void *memset(void *buf, char c, size_t n){
	uint8_t *p = (uint8_t *) buf; //its like temphead from actual head of linkedlist
	while(n--){ //can never be negative so will go till 0
		*p++ =c;	//set every bss character to 0
	return buf; //return the starting point
}	

void kernel_main(void){
	memset(__bss, 0, (size_t) __bss_end - (size_t) __bss);	//sets every bss to 0
	
	for (;;); //infinity
}	

__attribute__((section(".text.boot")))
__attribute__((naked))
void boot(void) {
	__asm__ __volatile(
		"mv sp, %[stack_top]\n" //set the stack ptr
		"j kernel_main\n" //jump to kernel main function
		:
		: [stack_top] "r" (__stack_top) //pass the stack top address as %[stack_top]
	);
}		
