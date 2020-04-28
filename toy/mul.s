	.text
	.file	"mul.cpp"
	.globl	_Z4imulll               # -- Begin function _Z4imulll
	.p2align	4, 0x90
	.type	_Z4imulll,@function
_Z4imulll:                              # @_Z4imulll
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, -16(%rbp)
	movq	%rsi, -8(%rbp)
	movq	-16(%rbp), %rax
	movq	-8(%rbp), %rcx
	imulq	%rcx, %rax
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end0:
	.size	_Z4imulll, .Lfunc_end0-_Z4imulll
	.cfi_endproc
                                        # -- End function
	.ident	"clang version 10.0.0 (https://github.com/llvm/llvm-project.git 2d2ebdfaf2f4427ee966c3810e0ed9a46559a402)"
	.section	".note.GNU-stack","",@progbits
