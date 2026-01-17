ENTRY(boot)

SECTIONS {
	. =0x80200000; /* start here */
	
	.text :{
		KEEP(*(.text.boot));
		*(.text .text.*);
	}
	
	.rodata :  ALIGN(4){
		*(.rodata .rodata.*);
	}
	
	.data : ALIGN(4) {
		*(.data .data.*); /* collect all data */
	}
	
	.bss : ALIGN(4) {
		__bss = .; /* mark start address of .bss */
		*(.bss .bss.* .sbss .sbss.*); /* collect all .bss variabled */
		__bss_end = .; /* mark end address of .bss */
	}
	
	. = ALIGN(4);
	. += 128 * 1024; /* 128 kb ki ram */
	__stack_top = .; /* top address of the ram */
}						
/*
The entry point of the kernel is the boot function.
The base address is 0x80200000.
The .text.boot section is always placed at the beginning.
Each section is placed in the order of .text, .rodata, .data, and .bss.
The kernel stack comes after the .bss section, and its size is 128KB.
*/
