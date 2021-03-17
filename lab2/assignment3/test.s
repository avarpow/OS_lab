	.file	"test.cpp"
	.text
	.section	.rodata
	.type	_ZStL19piecewise_construct, @object
	.size	_ZStL19piecewise_construct, 1
_ZStL19piecewise_construct:
	.zero	1
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.type	_ZStL13allocator_arg, @object
	.size	_ZStL13allocator_arg, 1
_ZStL13allocator_arg:
	.zero	1
	.type	_ZStL6ignore, @object
	.size	_ZStL6ignore, 1
_ZStL6ignore:
	.zero	1
	.globl	if_flag
	.bss
	.align 4
	.type	if_flag, @object
	.size	if_flag, 4
if_flag:
	.zero	4
	.globl	a1
	.align 4
	.type	a1, @object
	.size	a1, 4
a1:
	.zero	4
	.globl	a2
	.align 4
	.type	a2, @object
	.size	a2, 4
a2:
	.zero	4
	.globl	your_string
	.section	.rodata
	.align 4
.LC0:
	.string	"Mr.Chen, students and TAs are the best!\n"
	.section	.data.rel.local,"aw",@progbits
	.align 4
	.type	your_string, @object
	.size	your_string, 4
your_string:
	.long	.LC0
	.globl	while_flag
	.bss
	.align 4
	.type	while_flag, @object
	.size	while_flag, 4
while_flag:
	.zero	4
	.globl	random_buffer
	.align 4
	.type	random_buffer, @object
	.size	random_buffer, 4
random_buffer:
	.zero	4
	.text
	.globl	student_setting
	.type	student_setting, @function
student_setting:
.LFB2068:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	call	__x86.get_pc_thunk.ax
	addl	$_GLOBAL_OFFSET_TABLE_, %eax
	movl	$24, a1@GOTOFF(%eax)
	movl	$14, a2@GOTOFF(%eax)
	nop
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE2068:
	.size	student_setting, .-student_setting
	.globl	my_random
	.type	my_random, @function
my_random:
.LFB2069:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$20, %esp
	.cfi_offset 3, -12
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	call	rand@PLT
	movl	%eax, %ecx
	movl	$1321528399, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$3, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	imull	$26, %eax, %eax
	subl	%eax, %ecx
	movl	%ecx, %eax
	addl	$97, %eax
	movb	%al, -9(%ebp)
	movl	random_buffer@GOTOFF(%ebx), %eax
	movl	a2@GOTOFF(%ebx), %edx
	subl	$12, %edx
	addl	%eax, %edx
	movzbl	-9(%ebp), %eax
	movb	%al, (%edx)
	movzbl	-9(%ebp), %eax
	addl	$20, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE2069:
	.size	my_random, .-my_random
	.globl	print_a_char
	.type	print_a_char, @function
print_a_char:
.LFB2070:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$20, %esp
	.cfi_offset 3, -12
	call	__x86.get_pc_thunk.ax
	addl	$_GLOBAL_OFFSET_TABLE_, %eax
	movl	8(%ebp), %edx
	movb	%dl, -12(%ebp)
	movsbl	-12(%ebp), %edx
	subl	$8, %esp
	pushl	%edx
	movl	_ZSt4cout@GOT(%eax), %edx
	pushl	%edx
	movl	%eax, %ebx
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_c@PLT
	addl	$16, %esp
	nop
	movl	-4(%ebp), %ebx
	leave
	.cfi_restore 5
	.cfi_restore 3
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE2070:
	.size	print_a_char, .-print_a_char
	.section	.rodata
.LC1:
	.string	">>> test failed"
	.text
	.globl	test_failed
	.type	test_failed, @function
test_failed:
.LFB2071:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$4, %esp
	.cfi_offset 3, -12
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	subl	$8, %esp
	leal	.LC1@GOTOFF(%ebx), %eax
	pushl	%eax
	movl	_ZSt4cout@GOT(%ebx), %eax
	pushl	%eax
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	addl	$16, %esp
	movl	%eax, %edx
	subl	$8, %esp
	movl	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@GOT(%ebx), %eax
	pushl	%eax
	pushl	%edx
	call	_ZNSolsEPFRSoS_E@PLT
	addl	$16, %esp
	subl	$12, %esp
	pushl	$0
	call	exit@PLT
	.cfi_endproc
.LFE2071:
	.size	test_failed, .-test_failed
	.section	.rodata
.LC2:
	.string	">>> begin test"
.LC3:
	.string	"test can not run"
.LC4:
	.string	">>> if test pass!"
.LC5:
	.string	">>> while test pass!"
	.text
	.globl	main
	.type	main, @function
main:
.LFB2072:
	.cfi_startproc
	leal	4(%esp), %ecx
	.cfi_def_cfa 1, 0
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	.cfi_escape 0x10,0x5,0x2,0x75,0
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%ecx
	.cfi_escape 0xf,0x3,0x75,0x78,0x6
	.cfi_escape 0x10,0x3,0x2,0x75,0x7c
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	call	student_setting
	subl	$8, %esp
	leal	.LC2@GOTOFF(%ebx), %eax
	pushl	%eax
	movl	_ZSt4cout@GOT(%ebx), %eax
	pushl	%eax
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	addl	$16, %esp
	movl	%eax, %edx
	subl	$8, %esp
	movl	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@GOT(%ebx), %eax
	pushl	%eax
	pushl	%edx
	call	_ZNSolsEPFRSoS_E@PLT
	addl	$16, %esp
	movl	$0, if_flag@GOTOFF(%ebx)
	movl	a2@GOTOFF(%ebx), %eax
	cmpl	$11, %eax
	jle	.L7
	movl	a2@GOTOFF(%ebx), %eax
	subl	$11, %eax
	subl	$12, %esp
	pushl	%eax
	call	_Znaj@PLT
	addl	$16, %esp
	movl	%eax, while_flag@GOTOFF(%ebx)
	movl	a2@GOTOFF(%ebx), %eax
	subl	$11, %eax
	subl	$12, %esp
	pushl	%eax
	call	_Znaj@PLT
	addl	$16, %esp
	movl	%eax, random_buffer@GOTOFF(%ebx)
	movl	while_flag@GOTOFF(%ebx), %eax
	testl	%eax, %eax
	je	.L8
	movl	random_buffer@GOTOFF(%ebx), %eax
	testl	%eax, %eax
	jne	.L9
.L8:
	subl	$8, %esp
	leal	.LC3@GOTOFF(%ebx), %eax
	pushl	%eax
	movl	_ZSt4cout@GOT(%ebx), %eax
	pushl	%eax
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	addl	$16, %esp
	movl	%eax, %edx
	subl	$8, %esp
	movl	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@GOT(%ebx), %eax
	pushl	%eax
	pushl	%edx
	call	_ZNSolsEPFRSoS_E@PLT
	addl	$16, %esp
	subl	$12, %esp
	pushl	$-1
	call	exit@PLT
.L9:
	movl	a2@GOTOFF(%ebx), %eax
	subl	$11, %eax
	movl	%eax, %edx
	movl	while_flag@GOTOFF(%ebx), %eax
	subl	$4, %esp
	pushl	%edx
	pushl	$0
	pushl	%eax
	call	memset@PLT
	addl	$16, %esp
	movl	a2@GOTOFF(%ebx), %eax
	subl	$11, %eax
	movl	%eax, %edx
	movl	random_buffer@GOTOFF(%ebx), %eax
	subl	$4, %esp
	pushl	%edx
	pushl	$0
	pushl	%eax
	call	memset@PLT
	addl	$16, %esp
.L7:
	call	student_function@PLT
	movl	a1@GOTOFF(%ebx), %eax
	cmpl	$11, %eax
	jg	.L10
	movl	a1@GOTOFF(%ebx), %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	sarl	%eax
	leal	1(%eax), %edx
	movl	if_flag@GOTOFF(%ebx), %eax
	cmpl	%eax, %edx
	je	.L11
	call	test_failed
	jmp	.L11
.L10:
	movl	a1@GOTOFF(%ebx), %eax
	cmpl	$23, %eax
	jg	.L12
	movl	a1@GOTOFF(%ebx), %eax
	movl	$24, %edx
	subl	%eax, %edx
	movl	a1@GOTOFF(%ebx), %eax
	imull	%eax, %edx
	movl	if_flag@GOTOFF(%ebx), %eax
	cmpl	%eax, %edx
	je	.L11
	call	test_failed
	jmp	.L11
.L12:
	movl	a1@GOTOFF(%ebx), %eax
	sall	$4, %eax
	movl	%eax, %edx
	movl	if_flag@GOTOFF(%ebx), %eax
	cmpl	%eax, %edx
	je	.L11
	call	test_failed
.L11:
	subl	$8, %esp
	leal	.LC4@GOTOFF(%ebx), %eax
	pushl	%eax
	movl	_ZSt4cout@GOT(%ebx), %eax
	pushl	%eax
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	addl	$16, %esp
	movl	%eax, %edx
	subl	$8, %esp
	movl	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@GOT(%ebx), %eax
	pushl	%eax
	pushl	%edx
	call	_ZNSolsEPFRSoS_E@PLT
	addl	$16, %esp
	movl	random_buffer@GOTOFF(%ebx), %edx
	movl	while_flag@GOTOFF(%ebx), %eax
	subl	$8, %esp
	pushl	%edx
	pushl	%eax
	call	strcmp@PLT
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L13
	subl	$8, %esp
	leal	.LC5@GOTOFF(%ebx), %eax
	pushl	%eax
	movl	_ZSt4cout@GOT(%ebx), %eax
	pushl	%eax
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	addl	$16, %esp
	movl	%eax, %edx
	subl	$8, %esp
	movl	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@GOT(%ebx), %eax
	pushl	%eax
	pushl	%edx
	call	_ZNSolsEPFRSoS_E@PLT
	addl	$16, %esp
	jmp	.L14
.L13:
	call	test_failed
.L14:
	call	your_function@PLT
	movl	$0, %eax
	leal	-8(%ebp), %esp
	popl	%ecx
	.cfi_restore 1
	.cfi_def_cfa 1, 0
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	leal	-4(%ecx), %esp
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE2072:
	.size	main, .-main
	.type	_Z41__static_initialization_and_destruction_0ii, @function
_Z41__static_initialization_and_destruction_0ii:
.LFB2576:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$4, %esp
	.cfi_offset 3, -12
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	cmpl	$1, 8(%ebp)
	jne	.L18
	cmpl	$65535, 12(%ebp)
	jne	.L18
	subl	$12, %esp
	leal	_ZStL8__ioinit@GOTOFF(%ebx), %eax
	pushl	%eax
	call	_ZNSt8ios_base4InitC1Ev@PLT
	addl	$16, %esp
	subl	$4, %esp
	leal	__dso_handle@GOTOFF(%ebx), %eax
	pushl	%eax
	leal	_ZStL8__ioinit@GOTOFF(%ebx), %eax
	pushl	%eax
	movl	_ZNSt8ios_base4InitD1Ev@GOT(%ebx), %eax
	pushl	%eax
	call	__cxa_atexit@PLT
	addl	$16, %esp
.L18:
	nop
	movl	-4(%ebp), %ebx
	leave
	.cfi_restore 5
	.cfi_restore 3
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE2576:
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.type	_GLOBAL__sub_I_if_flag, @function
_GLOBAL__sub_I_if_flag:
.LFB2577:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	call	__x86.get_pc_thunk.ax
	addl	$_GLOBAL_OFFSET_TABLE_, %eax
	subl	$8, %esp
	pushl	$65535
	pushl	$1
	call	_Z41__static_initialization_and_destruction_0ii
	addl	$16, %esp
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE2577:
	.size	_GLOBAL__sub_I_if_flag, .-_GLOBAL__sub_I_if_flag
	.section	.init_array,"aw"
	.align 4
	.long	_GLOBAL__sub_I_if_flag
	.section	.text.__x86.get_pc_thunk.ax,"axG",@progbits,__x86.get_pc_thunk.ax,comdat
	.globl	__x86.get_pc_thunk.ax
	.hidden	__x86.get_pc_thunk.ax
	.type	__x86.get_pc_thunk.ax, @function
__x86.get_pc_thunk.ax:
.LFB2578:
	.cfi_startproc
	movl	(%esp), %eax
	ret
	.cfi_endproc
.LFE2578:
	.section	.text.__x86.get_pc_thunk.bx,"axG",@progbits,__x86.get_pc_thunk.bx,comdat
	.globl	__x86.get_pc_thunk.bx
	.hidden	__x86.get_pc_thunk.bx
	.type	__x86.get_pc_thunk.bx, @function
__x86.get_pc_thunk.bx:
.LFB2579:
	.cfi_startproc
	movl	(%esp), %ebx
	ret
	.cfi_endproc
.LFE2579:
	.hidden	__dso_handle
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
