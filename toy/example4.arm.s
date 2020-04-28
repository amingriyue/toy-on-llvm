	.text
	.syntax unified
	.eabi_attribute	67, "2.09"	@ Tag_conformance
	.eabi_attribute	6, 1	@ Tag_CPU_arch
	.eabi_attribute	8, 1	@ Tag_ARM_ISA_use
	.eabi_attribute	34, 1	@ Tag_CPU_unaligned_access
	.eabi_attribute	17, 1	@ Tag_ABI_PCS_GOT_use
	.eabi_attribute	20, 1	@ Tag_ABI_FP_denormal
	.eabi_attribute	21, 1	@ Tag_ABI_FP_exceptions
	.eabi_attribute	23, 3	@ Tag_ABI_FP_number_model
	.eabi_attribute	24, 1	@ Tag_ABI_align_needed
	.eabi_attribute	25, 1	@ Tag_ABI_align_preserved
	.eabi_attribute	38, 1	@ Tag_ABI_FP_16bit_format
	.eabi_attribute	18, 4	@ Tag_ABI_PCS_wchar_t
	.eabi_attribute	14, 0	@ Tag_ABI_PCS_R9_use
	.file	"example4.c"
	.globl	main                    @ -- Begin function main
	.p2align	2
	.type	main,%function
	.code	32                      @ @main
main:
	.fnstart
@ %bb.0:                                @ %entry
	sub	sp, sp, #32
	mov	r2, #0
	str	r2, [sp, #28]
	str	r0, [sp, #24]
	str	r1, [sp, #16]
	str	r2, [sp]
	str	r2, [sp, #12]
	b	.LBB0_1
.LBB0_1:                                @ %for.cond
                                        @ =>This Loop Header: Depth=1
                                        @     Child Loop BB0_3 Depth 2
                                        @       Child Loop BB0_5 Depth 3
                                        @     Child Loop BB0_11 Depth 2
	ldr	r0, [sp, #12]
	cmp	r0, #9
	bgt	.LBB0_16
	b	.LBB0_2
.LBB0_2:                                @ %for.body
                                        @   in Loop: Header=BB0_1 Depth=1
	mov	r0, #0
	str	r0, [sp, #8]
	b	.LBB0_3
.LBB0_3:                                @ %for.cond1
                                        @   Parent Loop BB0_1 Depth=1
                                        @ =>  This Loop Header: Depth=2
                                        @       Child Loop BB0_5 Depth 3
	ldr	r0, [sp, #8]
	cmp	r0, #9
	bgt	.LBB0_10
	b	.LBB0_4
.LBB0_4:                                @ %for.body3
                                        @   in Loop: Header=BB0_3 Depth=2
	mov	r0, #0
	str	r0, [sp, #4]
	b	.LBB0_5
.LBB0_5:                                @ %for.cond4
                                        @   Parent Loop BB0_1 Depth=1
                                        @     Parent Loop BB0_3 Depth=2
                                        @ =>    This Inner Loop Header: Depth=3
	ldr	r0, [sp, #4]
	cmp	r0, #9
	bgt	.LBB0_8
	b	.LBB0_6
.LBB0_6:                                @ %for.body6
                                        @   in Loop: Header=BB0_5 Depth=3
	ldr	r0, [sp]
	add	r0, r0, #1
	str	r0, [sp]
	b	.LBB0_7
.LBB0_7:                                @ %for.inc
                                        @   in Loop: Header=BB0_5 Depth=3
	ldr	r0, [sp, #4]
	add	r0, r0, #1
	str	r0, [sp, #4]
	b	.LBB0_5
.LBB0_8:                                @ %for.end
                                        @   in Loop: Header=BB0_3 Depth=2
	b	.LBB0_9
.LBB0_9:                                @ %for.inc8
                                        @   in Loop: Header=BB0_3 Depth=2
	ldr	r0, [sp, #8]
	add	r0, r0, #1
	str	r0, [sp, #8]
	b	.LBB0_3
.LBB0_10:                               @ %for.end10
                                        @   in Loop: Header=BB0_1 Depth=1
	mov	r0, #0
	str	r0, [sp, #8]
	b	.LBB0_11
.LBB0_11:                               @ %for.cond11
                                        @   Parent Loop BB0_1 Depth=1
                                        @ =>  This Inner Loop Header: Depth=2
	ldr	r0, [sp, #8]
	cmp	r0, #9
	bgt	.LBB0_14
	b	.LBB0_12
.LBB0_12:                               @ %for.body13
                                        @   in Loop: Header=BB0_11 Depth=2
	ldr	r0, [sp]
	add	r0, r0, #1
	str	r0, [sp]
	b	.LBB0_13
.LBB0_13:                               @ %for.inc15
                                        @   in Loop: Header=BB0_11 Depth=2
	ldr	r0, [sp, #8]
	add	r0, r0, #1
	str	r0, [sp, #8]
	b	.LBB0_11
.LBB0_14:                               @ %for.end17
                                        @   in Loop: Header=BB0_1 Depth=1
	b	.LBB0_15
.LBB0_15:                               @ %for.inc18
                                        @   in Loop: Header=BB0_1 Depth=1
	ldr	r0, [sp, #12]
	add	r0, r0, #1
	str	r0, [sp, #12]
	b	.LBB0_1
.LBB0_16:                               @ %for.end20
	mov	r0, #0
	str	r0, [sp, #12]
	b	.LBB0_17
.LBB0_17:                               @ %for.cond21
                                        @ =>This Loop Header: Depth=1
                                        @     Child Loop BB0_19 Depth 2
                                        @     Child Loop BB0_23 Depth 2
	ldr	r0, [sp, #12]
	cmp	r0, #19
	bgt	.LBB0_28
	b	.LBB0_18
.LBB0_18:                               @ %for.body23
                                        @   in Loop: Header=BB0_17 Depth=1
	mov	r0, #0
	str	r0, [sp, #8]
	b	.LBB0_19
.LBB0_19:                               @ %for.cond24
                                        @   Parent Loop BB0_17 Depth=1
                                        @ =>  This Inner Loop Header: Depth=2
	ldr	r0, [sp, #8]
	cmp	r0, #19
	bgt	.LBB0_22
	b	.LBB0_20
.LBB0_20:                               @ %for.body26
                                        @   in Loop: Header=BB0_19 Depth=2
	ldr	r0, [sp]
	add	r0, r0, #1
	str	r0, [sp]
	b	.LBB0_21
.LBB0_21:                               @ %for.inc28
                                        @   in Loop: Header=BB0_19 Depth=2
	ldr	r0, [sp, #8]
	add	r0, r0, #1
	str	r0, [sp, #8]
	b	.LBB0_19
.LBB0_22:                               @ %for.end30
                                        @   in Loop: Header=BB0_17 Depth=1
	mov	r0, #0
	str	r0, [sp, #8]
	b	.LBB0_23
.LBB0_23:                               @ %for.cond31
                                        @   Parent Loop BB0_17 Depth=1
                                        @ =>  This Inner Loop Header: Depth=2
	ldr	r0, [sp, #8]
	cmp	r0, #19
	bgt	.LBB0_26
	b	.LBB0_24
.LBB0_24:                               @ %for.body33
                                        @   in Loop: Header=BB0_23 Depth=2
	ldr	r0, [sp]
	add	r0, r0, #1
	str	r0, [sp]
	b	.LBB0_25
.LBB0_25:                               @ %for.inc35
                                        @   in Loop: Header=BB0_23 Depth=2
	ldr	r0, [sp, #8]
	add	r0, r0, #1
	str	r0, [sp, #8]
	b	.LBB0_23
.LBB0_26:                               @ %for.end37
                                        @   in Loop: Header=BB0_17 Depth=1
	b	.LBB0_27
.LBB0_27:                               @ %for.inc38
                                        @   in Loop: Header=BB0_17 Depth=1
	ldr	r0, [sp, #12]
	add	r0, r0, #1
	str	r0, [sp, #12]
	b	.LBB0_17
.LBB0_28:                               @ %for.end40
	ldr	r0, [sp]
	add	sp, sp, #32
	mov	pc, lr
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.fnend
                                        @ -- End function
	.ident	"clang version 10.0.0 (https://github.com/llvm/llvm-project.git c9276fbfdf0c7caf1576b2db562286d7cec7e53b)"
	.section	".note.GNU-stack","",%progbits
