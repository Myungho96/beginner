.section ".data"
n:	.word 0	!���� n
ary:	.skip 4*19*19	!�迭
fmt0:	.asciz "%d"
fmt3:	.asciz " n input = "
fmt4:	.asciz"%d\t"
fmt5:	.asciz"\n"

.section ".text"
	.global main

main:	save %sp,-96,%sp

reset:	set fmt3,%o0
	call printf		!"n input = "
	nop

	set fmt0,%o0
	set n,%o1
	call scanf		!n�Է�
	nop
	set n,%o0		!n�� %l0�� ����
	ld [%o0], %l0

	cmp %l0,2
	ble exit		!2���� ������
	
	cmp %l0,20
	bge exit		!20���� ū��

	mov 0, %l1	!i=0
	mov %l0, %l2	!j=n/2
	srl %l2,1,%l2
	mov 0, %l3	!temp=0
	

	mov %l0,%o0
	mov %l0,%o1
	call .mul
	nop
	mov %o0,%l7	!l7=n^2
	mov 0,%l5	!count=0
	
	set ary,%l4

clr_ary:
	cmp %l3,%l7 	!temp<n^2?
	be start
	nop
	sll %l3,2,%o0	!temp*4
	st %g0,[%l4+%o0]
	inc %l3
	ba clr_ary
	nop

start:	cmp %l5,%l7	!n^2�� �ݺ��Ұ���
	be print
	nop

full_ret:	
	mov %l1,%o0	!������ �迭�� á�ٸ� i=i+1,i=i%n�Ŀ� ����� ���ƿ�.
	mov %l0,%o1
	call .mul		!n*i
	nop

	add %o0,%l2,%l6	!%l6�� n*i + j ����
	sll %l6,2,%l6	!(n*i + j)*4
	ld [%l4+%l6], %l3	!temp�� ���� ������ ��ġ�� 0�� ����ֳ� Ȯ��
	cmp %l3,0
	be ary_inc
	nop

isfull:	add %g3,1,%l1	!���ִ� ��� ���� ������ i�� +1
	mov %l1,%o0
	mov %l0,%o1
	call .rem
	nop
	mov %o0,%l1

	mov %g4,%l2	!���� j �״�� �ִ´�

	ba full_ret
	nop

	
ary_inc:inc %l5
	st %l5,[%l4+%l6]	! count+1 ���� ������ ��ġ�� ����

	mov %l1,%g3	!���� i ����
	mov %l2,%g4	!���� j ����

	sub %l1,1,%l1	!i=i-1
	add %l1,%l0,%l1	!i=i-1+n
	mov %l1,%o0
	mov %l0,%o1
	call .rem		!n���� ���� ������
	nop
	mov %o0,%l1
	
	add %l2,1,%l2	!j=j+1
	mov %l2,%o0	!j+1�� n���� ���� ������
	mov %l0,%o1
	call .rem
	nop
	mov %o0,%l2

	ba start
	nop
	

print:	mov 0,%l3	!temp=0
	mov 0,%l5	!count=0
	
ploop:	cmp %l3,%l7 	!temp<n^2
	be reset
	nop
	
	sll %l3,2,%o0	!temp*4
	ld [%l4+%o0],%o1
	set fmt4,%o0
	call printf
	nop
	inc %l3
	inc %l5
	cmp %l5,%l0
	be space
	nop
	ba ploop
	nop
	

space:	set fmt5,%o0
	call printf
	nop
	mov 0,%l5
	ba ploop
	nop

	
exit:	ret
	restore