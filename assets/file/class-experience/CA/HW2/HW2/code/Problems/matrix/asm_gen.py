base_reg = ['x1', 'x2', 'x3']
regA = ['x4', 'x5', 'x6', 'x7']
regC = ['x8']
regB = []
for i in range(9, 25):
	regB.append('x'+str(i))


def lrA(k):
	for i in range(4):	
		print('lhu {}, {}(x1)'.format(regA[i], k*256+i*2))
def lB():
	for i in range(16):
		print('lhu {}, {}(x2)'.format(regB[i], (i // 4) * 256 + (i % 4) * 2))
def lC(i, j):
	print('lhu x8, {}(x3)'.format(256*i + 2*j))
def sC(i, j):
	print('sh x8, {}(x3)'.format(256*i + 2*j))


def Block_multi(shift_A, shift_B, shift_C):
	print('shift: {} {} {}'.format(shift_A, shift_B, shift_C))
	print('addi x1, x1, ' + str(shift_A))
	if shift_B == -31992:
		print('mv x2, x31')
	else:
		print('addi x2, x2, ' + str(shift_B))
	print('addi x3, x3, ' + str(shift_C))
	lB()
	for i in range(4):
		lrA(i)
		for j in range(4):
			lC(i, j)#sum = C[i][j]
			for k in range(4):
				print('mul x25, {}, {}'.format(regA[k], regB[4*k+j]))
				print('add x8, x8, x25')
				# C[i][j] += A[i][k] * b[k][j] 
			sC(i, j)
print('.global matrix_mul')
print('.type matrix_mul, %function')
print('.align 2')
print('matrix_mul:')
print('mv x1, a0')
print('mv x2, a1')
print('mv x3, a2')
print('mv x31, a1')

BSIZE = 4
pA, pB, pC = 0, 0, 0
for i in range(32):
	for j in range(32):
		for k in range(32):
			nA = 256 * BSIZE * i + BSIZE * 2 * j
			nB = 256 * BSIZE * j + BSIZE * 2 * k
			nC = 256 * BSIZE * i + BSIZE * 2 * k
			#C[i][k] = A[i][j]*B[j][k]
			Block_multi(nA - pA, nB - pB, nC - pC)
			pA = nA
			pB = nB
			pC = nC



#addi x1, a0, 