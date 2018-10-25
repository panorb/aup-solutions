	.file	"functions.c"
	.text
	.globl	_sum
	.def	_sum;	.scl	2;	.type	32;	.endef
_sum:
LFB10:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	movl	$0, -4(%ebp)
	movl	$1, -8(%ebp)
	jmp	L2
L3:
	movl	-8(%ebp), %eax
	addl	%eax, -4(%ebp)
	addl	$1, -8(%ebp)
L2:
	movl	-8(%ebp), %eax
	cmpl	8(%ebp), %eax
	jbe	L3
	movl	-4(%ebp), %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE10:
	.globl	_sumOdd
	.def	_sumOdd;	.scl	2;	.type	32;	.endef
_sumOdd:
LFB11:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	movl	$0, -4(%ebp)
	movl	$1, -8(%ebp)
	jmp	L6
L8:
	movl	8(%ebp), %eax
	andl	$1, %eax
	testl	%eax, %eax
	je	L7
	movl	-8(%ebp), %eax
	addl	%eax, -4(%ebp)
L7:
	addl	$1, -8(%ebp)
L6:
	movl	-8(%ebp), %eax
	cmpl	8(%ebp), %eax
	jbe	L8
	movl	-4(%ebp), %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE11:
	.globl	_digits
	.def	_digits;	.scl	2;	.type	32;	.endef
_digits:
LFB12:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	movl	$0, -4(%ebp)
	jmp	L11
L12:
	movl	8(%ebp), %eax
	movl	$-858993459, %edx
	mull	%edx
	movl	%edx, %eax
	shrl	$3, %eax
	movl	%eax, 8(%ebp)
	addl	$1, -4(%ebp)
L11:
	cmpl	$0, 8(%ebp)
	jne	L12
	movl	-4(%ebp), %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE12:
	.section .rdata,"dr"
LC0:
	.ascii "%d\0"
	.text
	.globl	_checksum1
	.def	_checksum1;	.scl	2;	.type	32;	.endef
_checksum1:
LFB13:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$56, %esp
	movl	$0, -12(%ebp)
	movl	8(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$LC0, 4(%esp)
	leal	-28(%ebp), %eax
	movl	%eax, (%esp)
	call	_sprintf
	movl	$0, -16(%ebp)
	jmp	L15
L16:
	leal	-28(%ebp), %edx
	movl	-16(%ebp), %eax
	addl	%edx, %eax
	movzbl	(%eax), %eax
	movsbl	%al, %edx
	movl	-12(%ebp), %eax
	addl	%edx, %eax
	subl	$48, %eax
	movl	%eax, -12(%ebp)
	addl	$1, -16(%ebp)
L15:
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_digits
	leal	-1(%eax), %edx
	movl	-16(%ebp), %eax
	cmpl	%eax, %edx
	ja	L16
	movl	-12(%ebp), %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE13:
	.ident	"GCC: (MinGW.org GCC-6.3.0-1) 6.3.0"
	.def	_sprintf;	.scl	2;	.type	32;	.endef
