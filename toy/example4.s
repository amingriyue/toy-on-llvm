	.text
	.file	"example4.c"
	.globl	main                    # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movl	$0, -24(%rbp)
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	movl	$0, -8(%rbp)
	movl	$0, -12(%rbp)
	jmp	.LBB0_1
.LBB0_1:                                # %for.cond
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_3 Depth 2
                                        #       Child Loop BB0_5 Depth 3
                                        #     Child Loop BB0_11 Depth 2
	movl	-12(%rbp), %eax
	subl	$9, %eax
	jg	.LBB0_16
	jmp	.LBB0_2
.LBB0_2:                                # %for.body
                                        #   in Loop: Header=BB0_1 Depth=1
	movl	$0, -4(%rbp)
	jmp	.LBB0_3
.LBB0_3:                                # %for.cond1
                                        #   Parent Loop BB0_1 Depth=1
                                        # =>  This Loop Header: Depth=2
                                        #       Child Loop BB0_5 Depth 3
	movl	-4(%rbp), %eax
	subl	$9, %eax
	jg	.LBB0_10
	jmp	.LBB0_4
.LBB0_4:                                # %for.body3
                                        #   in Loop: Header=BB0_3 Depth=2
	movl	$0, -16(%rbp)
	jmp	.LBB0_5
.LBB0_5:                                # %for.cond4
                                        #   Parent Loop BB0_1 Depth=1
                                        #     Parent Loop BB0_3 Depth=2
                                        # =>    This Inner Loop Header: Depth=3
	movl	-16(%rbp), %eax
	subl	$9, %eax
	jg	.LBB0_8
	jmp	.LBB0_6
.LBB0_6:                                # %for.body6
                                        #   in Loop: Header=BB0_5 Depth=3
	movl	-8(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -8(%rbp)
	jmp	.LBB0_7
.LBB0_7:                                # %for.inc
                                        #   in Loop: Header=BB0_5 Depth=3
	movl	-16(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -16(%rbp)
	jmp	.LBB0_5
.LBB0_8:                                # %for.end
                                        #   in Loop: Header=BB0_3 Depth=2
	jmp	.LBB0_9
.LBB0_9:                                # %for.inc8
                                        #   in Loop: Header=BB0_3 Depth=2
	movl	-4(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -4(%rbp)
	jmp	.LBB0_3
.LBB0_10:                               # %for.end10
                                        #   in Loop: Header=BB0_1 Depth=1
	movl	$0, -4(%rbp)
	jmp	.LBB0_11
.LBB0_11:                               # %for.cond11
                                        #   Parent Loop BB0_1 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movl	-4(%rbp), %eax
	subl	$9, %eax
	jg	.LBB0_14
	jmp	.LBB0_12
.LBB0_12:                               # %for.body13
                                        #   in Loop: Header=BB0_11 Depth=2
	movl	-8(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -8(%rbp)
	jmp	.LBB0_13
.LBB0_13:                               # %for.inc15
                                        #   in Loop: Header=BB0_11 Depth=2
	movl	-4(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -4(%rbp)
	jmp	.LBB0_11
.LBB0_14:                               # %for.end17
                                        #   in Loop: Header=BB0_1 Depth=1
	jmp	.LBB0_15
.LBB0_15:                               # %for.inc18
                                        #   in Loop: Header=BB0_1 Depth=1
	movl	-12(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -12(%rbp)
	jmp	.LBB0_1
.LBB0_16:                               # %for.end20
	movl	$0, -12(%rbp)
	jmp	.LBB0_17
.LBB0_17:                               # %for.cond21
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_19 Depth 2
                                        #     Child Loop BB0_23 Depth 2
	movl	-12(%rbp), %eax
	subl	$19, %eax
	jg	.LBB0_28
	jmp	.LBB0_18
.LBB0_18:                               # %for.body23
                                        #   in Loop: Header=BB0_17 Depth=1
	movl	$0, -4(%rbp)
	jmp	.LBB0_19
.LBB0_19:                               # %for.cond24
                                        #   Parent Loop BB0_17 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movl	-4(%rbp), %eax
	subl	$19, %eax
	jg	.LBB0_22
	jmp	.LBB0_20
.LBB0_20:                               # %for.body26
                                        #   in Loop: Header=BB0_19 Depth=2
	movl	-8(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -8(%rbp)
	jmp	.LBB0_21
.LBB0_21:                               # %for.inc28
                                        #   in Loop: Header=BB0_19 Depth=2
	movl	-4(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -4(%rbp)
	jmp	.LBB0_19
.LBB0_22:                               # %for.end30
                                        #   in Loop: Header=BB0_17 Depth=1
	movl	$0, -4(%rbp)
	jmp	.LBB0_23
.LBB0_23:                               # %for.cond31
                                        #   Parent Loop BB0_17 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movl	-4(%rbp), %eax
	subl	$19, %eax
	jg	.LBB0_26
	jmp	.LBB0_24
.LBB0_24:                               # %for.body33
                                        #   in Loop: Header=BB0_23 Depth=2
	movl	-8(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -8(%rbp)
	jmp	.LBB0_25
.LBB0_25:                               # %for.inc35
                                        #   in Loop: Header=BB0_23 Depth=2
	movl	-4(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -4(%rbp)
	jmp	.LBB0_23
.LBB0_26:                               # %for.end37
                                        #   in Loop: Header=BB0_17 Depth=1
	jmp	.LBB0_27
.LBB0_27:                               # %for.inc38
                                        #   in Loop: Header=BB0_17 Depth=1
	movl	-12(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -12(%rbp)
	jmp	.LBB0_17
.LBB0_28:                               # %for.end40
	movl	-8(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.ident	"clang version 10.0.0 (https://github.com/llvm/llvm-project.git c9276fbfdf0c7caf1576b2db562286d7cec7e53b)"
	.section	".note.GNU-stack","",@progbits
