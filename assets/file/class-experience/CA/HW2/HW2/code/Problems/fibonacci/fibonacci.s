.global fibonacci
.type fibonacci, %function

.align 2
# unsigned long long int fibonacci(int n);
fibonacci:	addi sp, sp, -800
		addi t1, sp, 0 # arr pointer
		addi t2, x0, 0
		addi t3, x0, 1
		addi t5, x0, 0 # i = 0
		addi t6, x0, 94 # x7 = 94
Loop:		beq t5, t6, End # if i == 94, break
		add t4, t3, t2 # a[i+2] = a[i+1] + a[i]
		sd t2, 0(t1) # a[i] save in stack
		add t2, t3, x0 # x29 = a[i] = a[i+1]
		add t3, t4, x0 # x30 = a[i+1] = a[i+2]
		addi t1, t1, 8 # arrp += 8
		addi t5, t5, 1 # i++
		beq x0, x0, Loop # go to Loop
End:		sd t2, 0(t1) # a[96] saved in stack
		sd t3, 8(t1) # a[97] saved in stack
		slli a0, a0, 3 # k = k * 8
		add a0, sp, a0 # move to a[k] 
		ld a0, 0(a0) # return a[k]
		addi sp, sp, 800
		ret   

