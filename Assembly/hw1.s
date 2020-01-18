fmt2:	.asciz "input="
fmt4:	.asciz "%d"
		.align 4


		.global	main,scanf,printf
main:	save %sp,-104,%sp
loop:	set fmt2,%o0
		call printf
		nop

		set fmt4,%o0
		call scanf
		add %fp,-4,%o1

		ld [%fp-4],%l1
		subcc %l1,0,%g0
		bl exit_r
		nop

		set fmt2,%o0
		call printf
		nop

		set fmt4,%o0
		add %fp,-8,%o1
		call scanf
		nop

		ld [%fp-8],%l2

		mov %g0,%l7
		loop_r:	subcc %l1,%l2,%g0
				bg loop
				nop
				add %l1,%l7,%l7
				
				ba loop_r
rr:				inc %l1
exit_r:	ret
		restore

