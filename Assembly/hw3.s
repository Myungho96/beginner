fmt1:	.asciz "input = "
fmt2: 	.asciz "%d"
fmt3:	.asciz "output = prime number\n"
fmt4:	.asciz "output = non-prime number(%d)\n"
	.align 4
	.global main, scanf, printf
 
main:	save %sp, -104, %sp

loop:	set fmt1, %o0
	call printf
	nop
	set fmt2, %o0
	add %fp, -4, %o1
	call scanf
	nop

	ld [%fp-4], %l0
	cmp %l0, 1
	ble exit
	nop
	clr %l1
	mov %l0, %l3
	mov 1, %l2

count:	mov %l0, %o0
	mov %l3, %o1
	call .rem               ! %o0 = input
	nop

	cmp %o0, 0
	be multi
	nop

	sub %l3, 1, %l3
	subcc %l3, 1, %g0
	bg count
	nop

	ba prime
	nop

multi:	mov %l3, %o0
	mov %l2, %o1
	call .mul
	nop
	mov %o0, %l2
	inc %l1                 ! counter++
	sub %l3, 1, %l3
	subcc %l3, 1, %g0
	bg count
	nop

	ba prime
	nop

 prime:
	cmp %l1, 1
	bne NonPrime
	nop

 IsPrime:
	set fmt3, %o0
	call printf
	nop

	ba loop
	nop

 NonPrime:
	mov %l2, %o0
	mov %l0, %o1
	call .div
	nop
	mov %o0, %l2
	set fmt4, %o0
	mov %l2, %o1
	call printf
	nop

	ba loop
	nop

exit:	ret
	restore