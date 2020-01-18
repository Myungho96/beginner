fmt0:	.asciz "%d"
fmt2:	.asciz "input = "
fmt3:	.asciz "output = %d\n"
	.align 4
	.global main
main:	save %sp,-112,%sp

reset:	set fmt2,%o0
	call printf		!"input = "
	nop
	
	set fmt0,%o0
	add %fp,-4,%o1	!첫번째 수 입력받는다
	call scanf
	nop
	
	ld [%fp-4],%l0	!음수인지 비교,l0=첫번째수
	cmp %l0,0
	ble exit
	nop

	set fmt2,%o0
	call printf		!"input = "
	nop
	
	set fmt0,%o0
	add %fp,-8,%o1	!두번째 수 입력받는다
	call scanf
	nop	

	set fmt2,%o0
	call printf		!"input = "
	nop
	
	set fmt0,%o0
	add %fp,-12,%o1	!세번째 수 입력받는다
	call scanf
	nop

a:	ld [%fp-12],%l1	!1인지 2인지
	cmp %l1,1
	be ready1
	nop

	cmp %l1,2
	be ready2
	nop


print:	set fmt3,%o0
	mov %l5,%o1
	call printf
	nop
	ba reset
	nop

ready1:	ld [%fp-4],%o0
	ld [%fp-8],%o1
	call sub1
	nop
	mov %o0,%l5	!l5=output
	ba print
	nop

ready2:	ld [%fp-4],%o0
	ld [%fp-8],%o1
	call sub2
	nop
	mov %o0,%l5	!l5=output
	ba print
	nop

sub1:	save %sp,-96,%sp
	mov %i0,%l2	!첫번째 수 복사
	mov %i0,%l3	!첫번째 수 복사
	mov 0,%l1	!l1=sum
	sub %i1,%i0,%l5	!두 수 사이의 차이
	mov 0,%l4	!i=0

loop:	cmp %l4,%l5	!두수의차가 카운터보다 작은지
	bg exit_sub1
	nop
	mov %l2,%o0
	mov %l3,%o1
	call .mul		!제곱해줌
	nop
	add %l1,%o0,%l1	!sum에 더함
	inc %l2
	inc %l3
	inc %l4
	ba loop
	nop
	
exit_sub1:	mov %l1,%i0
	ret
	restore

sub2:	sub %o1,%o0,%o2	!두 수 사이의 차이
	mov %o0,%o4
	mov 0,%o5	!i=0

loop2:	cmp %o5,%o2	!두수의차가 카운터보다 작은지
	bge exit_sub2
	nop
	inc %o4
	add %o0,%o4,%o0	!sum에 더함
	inc %o5
	ba loop2
	nop
	
exit_sub2:
	jmpl %o7+8,%g0
	nop



exit:	ret
	restore