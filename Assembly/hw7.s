	.section ".data"
x:	.word 0 !싱글포맷 공간
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
	st %f6,[%fp-4]	!대피

loop:	set fmt1,%o0	!input=
	call printf
	nop

	set fmt2,%o0	!scanf n
	set x,%o1
	call scanf
	nop
	
	set x,%l0		!x불러오기
	ld[%l0],%f3	!f3에 저장

	set exittest,%l0	!999불러옴
	ld[%l0],%f4	!f4에 저장


	fcmps %f3, %f4	!999인가?
	nop

	fbe print
	nop

	set min,%l0
	ld[%l0],%f5	!min을 f5에 저장

	fcmps %f3,%f5	!1.0보다큰가?
	nop

	fbge sum
	nop

	fba loop
	nop

sum:	ld [%fp-4],%f6
	fadds %f6,%f3,%f6
	st %f6,[%fp-4]	!대피
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
	
	
	