.global matrix_mul
.type matrix_mul, %function

.align 2
# void matrix_mul(unsigned short A[][], unsigned short B[][], unsigned short C[][]);
matrix_mul:
	    	addi	sp, sp, -136
	    	sd		s0, 0(sp) # used
	    	sd      s1, 8(sp) # used
	    	sd		s2, 16(sp) # kk + bsize
	    	sd		s3, 24(sp)
		    sd		s4, 32(sp) # jj + bsize
		    sd		s5, 40(sp) # kk
		    sd		s6, 48(sp) ## jj
		    sd		s7, 56(sp) # bsize
		    sd		s8, 64(sp) # SIZE
		    sd		s9, 72(sp) # i
		    sd		s10, 80(sp) # j
		    sd		s11, 88(sp) # k
		    sd		a3, 96(sp)
		    sd 		a4, 104(sp)
		    sd 		a5, 112(sp)
		    sd 		a6, 120(sp)
		    sd 		a7, 128(sp)

		    addi	s7, zero, 32 # bsize = 16
		    addi	s8, zero, 256 # SIZE = 256

		    addi	s6, zero, 0 # jj = 0
Cyclejj:		
			add 	s4, s6, s7 # s4 = jj + bsize

			addi	s5, zero, 0 # kk = 0			
Cyclekk:
			add 	s2, s5, s7 # s2 = kk + bsize

			addi	s9, zero, 0 # i = 0
Cyclei:
			slli 	t0, s9, 7 # t0 = i * 128 for A

			slli 	s0, s9, 7 # s0 = i * 128 for C

			add		s10, s6, zero # j = jj
Cyclej:		
			add 	t5, t0, s10 # t5 = t0 + j for A
			add 	t5, t5, a0 # A[i][j] for A
			lhu 	t5, 0(t5) # load A[i][j] for A

			slli 	t6, s10, 7 # t6 = j * 128 for B

			add 	s11, s5, zero # k = kk

Cyclek:
			add 	t1, t6, s11 # t1 = t6 + k for B
			add 	t1, t1, a1 # B[j][k] for B
			lhu 	s3, 0(t1) # load B[j][k] for B
			lhu		a3, 2(t1)
			lhu		a4, 4(t1)
			lhu		a5, 6(t1)

			add 	t2, s0, s11 # t2 = s0 + k for C
			add 	t2, t2, a2 # C[i][k] for C
			lhu 	t3, 0(t2) # load C[i][k] for C
			lhu		a6, 2(t2)
			lhu		a7, 4(t2)
			lhu		s1, 6(t2)

			mul 	t4, t5, s3 # t4 = A[i][j]*B[j][k]
			add 	t3, t3, t4 # C[i][k] += t4
			sh 		t3, 0(t2) # store C[i][k]

			mul 	t4, t5, a3 # t4 = A[i][j]*B[j][k]
			add 	a6, a6, t4 # C[i][k] += t4
			sh 		a6, 2(t2) # store C[i][k]

			mul 	t4, t5, a4 # t4 = A[i][j]*B[j][k]
			add 	a7, a7, t4 # C[i][k] += t4
			sh 		a7, 4(t2) # store C[i][k]

			mul 	t4, t5, a5 # t4 = A[i][j]*B[j][k]
			add 	s1, s1, t4 # C[i][k] += t4
			sh 		s1, 6(t2) # store C[i][k]

			addi 	s11, s11, 8 # k+=8
			bne		s11, s2, Cyclek # if k != kk + bsize continue
#OutCyclek:
			addi	s10, s10, 2 # j+=2
			bne		s10, s4, Cyclej # if j != jj + bsize continue
#OutCyclej:		
			addi	s9, s9, 2 # i+=2
			bne		s9, s8, Cyclei # if i != 128 continue
#OutCyclei:
			
			add		s5, s5, s7 # kk += bsize
			bne		s5, s8, Cyclekk # if kk != 128 continue
#OutCyclekk:
				
			add 	s6, s6, s7 # jj += bsize
			bne 	s6, s8, Cyclejj # if jj != 128 continue
#OutCyclejj:


			addi 	t2, zero, 1 # t2 = 1
			slli 	t2, t2, 16 # t2 <<= 16
			add 	t2, t2, a2 # t2 = C[SIZE][SIZE]
			addi	t1, a2, 0 # t1 = &C[0][0]
Mod:
			lhu		t3, 0(t1) # load t3 = &C[i][j] /
			andi	t3, t3, 1023 # t3 &= 1023 /
			sh 		t3, 0(t1) # store t3 in t1 /
			addi 	t1, t1, 2 # t1 += 2
			bne		t1, t2, Mod # if t1 != t2 continue
# EndMod
			ld		s0, 0(sp) # A[i]
	    	ld      s1, 8(sp) # B[j]
	    	ld		s2, 16(sp) # C[k]
	    	ld		s3, 24(sp) 
		    ld		s4, 32(sp)
		    ld		s5, 40(sp)
		    ld		s6, 48(sp)
		    ld		s7, 56(sp)
		    ld		s8, 64(sp)
		    ld		s9, 72(sp) # int i
		    ld		s10, 80(sp) # int j
		    ld		s11, 88(sp) # int k
		    sd		a3, 96(sp)
		    sd 		a4, 104(sp)
		    sd 		a5, 112(sp)
		    sd 		a6, 120(sp)
		    sd 		a7, 128(sp)
    		addi    sp, sp, 136
    		ret
    # insert code here
    # Green card here: https://www.cl.cam.ac.uk/teaching/1617/ECAD+Arch/files/docs/RISCVGreenCardv8-20151013.pdf
    # Matrix multiplication: https://en.wikipedia.org/wiki/Matrix_multiplication
