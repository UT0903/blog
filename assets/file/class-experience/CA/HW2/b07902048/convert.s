.global convert
.type convert, %function

.align 2
# int convert(char *);
convert:	add t1, zero, zero # t1 = minus = 0
			add t3, zero, zero # t3 = sum = 0
			lb t4, 0(a0)
			addi t6, zero, 43
			bne t4, t6, Else # if str[i] != '+'
			addi a0, a0, 1 # i++
			beq zero, zero, Exit

Else:		addi t5, zero, 45
			bne t4, t5, Exit # if str[i] != '-'
			addi t1, zero, 1 # minus = 1
			addi a0, a0, 1 # i++
			
Exit:		addi t5, zero, 48 # t5 = 48
			addi t6, zero, 58 # t6 = 58
			lb t4, 0(a0)
			beq t4, zero, Break # if str[i] == 0
			
			blt t4, t5, Isnotdigit # if str[i] < 48
			bge t4, t6, Isnotdigit # if str[i] >= 58
			beq zero, zero, Isdigit # go to Isdigit
Isnotdigit:	addi a0, zero, -1 # return -1
			ret   
Isdigit:	addi t2, zero, 10 # t2 = 10
			mul t3, t3, t2 # sum *= 10
			add t3, t3, t4 # sum += str[i]
			addi t3, t3, -48 # sum -= '0'
			addi a0, a0, 1 # i++
			beq zero, zero, Exit
Break:		beq t1, zero, Next # if minus == 0
			sub t3, zero, t3 # sum = -sum
Next:		addi a0, t3, 0 # return t3(sum)
			ret


