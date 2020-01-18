fmt1:	.asciz "n="
fmt2:	.asciz "input="
fmt4:	.asciz "%d"
fmt5:	.asciz "result=%x\n"
		.align 4


		.global	main,scanf,printf
main:	save %sp,-104,%sp
loop:	set fmt2,%o0
		call printf
		nop

		set fmt4,%o0
		add %fp,-4,%o1
		call scanf
		nop

		ld [%fp-4],%l0

loop2:		set fmt1,%o0
		call printf
		nop

		set fmt4,%o0
		add %fp,-8,%o1
		call scanf
		nop

		ld [%fp-8],%l1
		subcc %l1,0,%g0
		bl exit_r
		nop

		mov 32,%l2

		sub %l2,%l1,%l3

		srl %l0,%l1,%l7
		sll %l0,%l3,%l6
		
		add %l7,%l6,%l7

		set fmt5,%o0
		mov %l7,%o1
		call printf
		nop
		


		ba loop2
		nop
exit_r:	ret
		restore

