	.section ".data"
x:	.word 0 !�̱����� ����
exittest:	.single 0r999.0
min:	.single 0r1.0
zero:	.single 0r0.0
fmt1:	.asciz "input="
fmt2:	.asciz "%g"
fmt3:	.asciz "output=%g\n"

	.section ".text"
	.global main

main:	save %sp, -104, %sp
	set zero,%l0	!f6=sum
	ld[%l0],%f6
	st %f6,[%fp-4]	!����

loop:	set fmt1,%o0	!input=
	call printf
	nop

	set fmt2,%o0	!scanf n
	set x,%o1
	call scanf
	nop
	
	set x,%l0		!x�ҷ�����
	ld[%l0],%f3	!f3�� ����

	set exittest,%l0	!999�ҷ���
	ld[%l0],%f4	!f4�� ����


	fcmps %f3, %f4	!999�ΰ�?
	nop

	fbe print
	nop

	set min,%l0
	ld[%l0],%f5	!min�� f5�� ����

	fcmps %f3,%f5	!1.0����ū��?
	nop

	fbge sum
	nop

	fba loop
	nop

sum:	ld [%fp-4],%f6
	fadds %f6,%f3,%f6
	st %f6,[%fp-4]	!����
	ba loop
	nop

	

print:	ld [%fp-4],%f6
	fstod %f6,%f2
	std %f2,[%fp-8]
	ldd [%fp-8],%o2
	mov %o2,%o1
	mov %o3,%o2
	set fmt3,%o0
	call printf
	nop

exit:	ret
	restore
	
	
	