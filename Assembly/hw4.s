fmt0:	.asciz "%d"
fmt1:	.asciz "array element is "
fmt2:	.asciz "array input="
fmt3:	.asciz "n input="
fmt4:	.asciz"%d  "
fmt5:	.asciz"\n"
	.align 4
	.global main
main:	save %sp,-160,%sp

loop:	set fmt3,%o0
	call printf
	nop

	set fmt0,%o0
	add %fp,-4,%o1
	call scanf
	nop

	ld [%fp-4],%l0	!load n
	cmp %l0,2
	ble exit_r
	cmp %l0,15
	bg exit_r
	nop

	add %fp, -64, %l1	!%fp - 64
	mov 0,%l2
	mov 0,%l3	!int i=0
	mov 0,%l4	!int j=0
	
insert_a:
	cmp %l2,%l0
	bge outer_test
	nop
	set fmt2, %o0
	call printf
	nop
	sll %l2,2,%o2	!4*i
	set fmt0, %o0
	add %l1,%o2,%o1
	call scanf
	nop
	inc %l2
	ba insert_a
	nop

inner:
	sll %l3,2,%o0	!4*i
	ld[%l1+%o0],%l5	!load arr[i]
	sll %l4,2,%o0	!4*j
	ld[%l1+%o0],%l6	!load arr[j]

	cmp %l5,%l6
	bge inner_inc
	nop
	mov %l5,%l2
	mov %l6,%l5
	sll %l3,2,%o0	!4*j
	st %l5,[%l1+%o0]	!save arr[i]

	mov %l2,%l6
	sll %l4,2,%o0	!4*j
	st %l6,[%l1+%o0]	!save arr[i]



inner_inc:
	add %l4,1,%l4	!j++

inner_test:
	cmp %l4,%l0
	bl inner
	nop
outer_inc:
	add %l3,1,%l3

outer_test:
	cmp %l3,%l0
	bl,a inner_test
	add %l3,1,%l4
	ba print
	nop

print:
	set fmt1,%o0
	call printf
	mov 0,%l2	!int i=0

loop2:	cmp %l2,%l0
	bge enter
	nop
	sll %l2,2,%o0	!4*i
	ld[%l1+%o0],%o1	!load arr[i]
	set fmt4,%o0
	call printf
	nop
	inc %l2
	ba loop2
	nop
enter:
	set fmt5,%o0
	call printf
	nop
	ba loop
	nop

exit_r:	ret
	restore
	