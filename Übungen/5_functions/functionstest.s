	.file	"functionstest.c"
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
LC0:
	.ascii "sum(%d) = %d\12\0"
LC1:
	.ascii "sumOdd(%d) = %d\12\0"
LC2:
	.ascii "digits(%d) = %d\12\0"
LC3:
	.ascii "checksum1(%d) = %d\12\0"
	.text
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
LFB10:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	andl	$-16, %esp
	subl	$16, %esp
	call	___main
	movl	$3, (%esp)
	call	_sum
	movl	%eax, 8(%esp)
	movl	$3, 4(%esp)
	movl	$LC0, (%esp)
	call	_printf
	movl	$3, (%esp)
	call	_sumOdd
	movl	%eax, 8(%esp)
	movl	$3, 4(%esp)
	movl	$LC1, (%esp)
	call	_printf
	movl	$3, (%esp)
	call	_digits
	movl	%eax, 8(%esp)
	movl	$3, 4(%esp)
	movl	$LC2, (%esp)
	call	_printf
	movl	$3, (%esp)
	call	_digits
	movl	%eax, 8(%esp)
	movl	$3, 4(%esp)
	movl	$LC3, (%esp)
	call	_printf
	movl	$0, %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE10:
	.ident	"GCC: (MinGW.org GCC-6.3.0-1) 6.3.0"
	.def	_sum;	.scl	2;	.type	32;	.endef
	.def	_printf;	.scl	2;	.type	32;	.endef
	.def	_sumOdd;	.scl	2;	.type	32;	.endef
	.def	_digits;	.scl	2;	.type	32;	.endef
