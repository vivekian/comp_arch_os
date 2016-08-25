	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 11
	.globl	__Z8add_numsii              ## globl makes the symbol visible to ld. 
	.align	4, 0x90
__Z8add_numsii:                         ## @_Z8add_numsii
	.cfi_startproc
## BB#0:
	pushq	%rbp                        ## pushq p
Ltmp0:
	.cfi_def_cfa_offset 16
Ltmp1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp2:
	.cfi_def_cfa_register %rbp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	-4(%rbp), %esi
	addl	-8(%rbp), %esi
	movl	%esi, %eax
	popq	%rbp
	retq
	.cfi_endproc

	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	pushq	%rbp                        ## save the current active frame
Ltmp3:
	.cfi_def_cfa_offset 16
Ltmp4:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp                  ## make the current stack pointer as base pointer.
Ltmp5:
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp                   ## allocate 16 bytes of memory for stack 
	movl	$2, %edi                    ## move 2 to the first argument register 
	movl	$3, %esi                    ## move 3 to the second argument register 
	movl	$0, -4(%rbp)                ## move 0 to first local on stack 
	callq	__Z8add_numsii              ## call into add_num() 
	xorl	%esi, %esi                  ## zero out to esi which is what we return from main.
	movl	%eax, -8(%rbp)              
	movl	%esi, %eax
	addq	$16, %rsp                   ## move stack pointer 
	popq	%rbp                        ## pop out base pointer saved at the beginning.
	retq
	.cfi_endproc


.subsections_via_symbols
