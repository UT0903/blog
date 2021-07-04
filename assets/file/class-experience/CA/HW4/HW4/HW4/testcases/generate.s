.global store_test
store_test:  
    addi t0, zero, 3
    sd   t0, 56(a0)
    sd   t0, 64(a0)
    addi t1, zero, 5
    sd   t1, 72(a0)
    sd   t1, 1016(a0)
    ret                  # eof

.global load_test
load_test:  
    addi t0, zero, 3
    sd   t0, 56(a0)
    sd   t0, 72(a0)
    ld   t1, 72(a0)
    ld   t2, 56(a0)
    addi t2, t1, 128
    sd   t1, 128(a0)
    sd   t2, 256(a0)
    ret                  # eof

.global add_sub_test
add_sub_test:  
    addi t0, zero, 3
    addi t1, zero, 4
    add t2, t0, t1
    sub t3, t1, t0
    sd   t2, 64(a0)
    sd   t3, 80(a0)
    ret                  # eof

.global and_or_xor_test
and_or_xor_test:  
    addi t0, zero, 123
    addi t1, zero, 456
    and t2, t0, t1
    and t3, t1, t0
    or  t4, t0, t1
    or  t5, t1, t0
    xor t0, t2, t3
    xor t1, t4, t5
    sd   t0, 64(a0)
    sd   t1, 0(a0)
    sd   t2, 8(a0)
    sd   t3, 16(a0)
    sd   t4, 128(a0)
    sd   t5, 80(a0)
    ret                  # eof


.global andi_ori_xori_test
andi_ori_xori_test:  
    addi t0, zero, 123
    addi t1, zero, 456
    andi t2, t0, 789
    ori  t3, t0, 789
    xori t4, t0, 789
    sd   t2, 8(a0)
    sd   t3, 16(a0)
    sd   t4, 32(a0)
    ret                  # eof

.global slli_srli_test
slli_srli_test:
    addi t0, zero, 123
    addi t1, zero, 456
    slli t2, t0, 1
    srli t3, t0, 1
    sd   t2, 16(a0)
    sd   t3, 32(a0)
    ret                  # eof

.global bne_beq_test
bne_beq_test:
    addi t0, zero, 123
    addi t1, zero, 456
    addi t2, zero, 123
    bne t0, t1, b1
    sd t1, 16(a0)
    sd t2, 24(a0)
b1:
    sd t0, 32(a0)
    beq t0, t1, b2
    sd t1, 40(a0)
    sd t2, 48(a0)
    sd t0, 56(a0)
b2:
    sd t1, 64(a0)
    sd t0, 1016(a0)
    ret                  # eof

.global workload1
workload1:
    xor a5, a6, a6    # a5 = 0
    xor a6, a5, a5    # a6 = 0
    addi a4, a5, 1    # a4 = 1
    addi a1, a0, 4    # a1 = array address + 4
    addi a2, a5, 134
    addi a3, a5, 177
    addi t3, a5, 200  # t3 = 200
    add t0, a5, a6    # t0 = 0
L1:
    add t1, t0, a5    # t1 = 0
    addi a2, a2, 999
    add t2, t1, a5    # t2 = 0
    addi a3, a3, 888
    ld t4, 0(a0)
    ld t5, 16(a0)
    ld t6, 8(a0)
    addi t4, t4, 77
    addi t5, t4, 77
    addi t6, t4, 77
    add t4, t5, t6
    or t4, t4, t6
    and t5, a2, t5
    xori t5, t6, 1
    andi t6, t4, 111
    slli t6, t5, 1
    slli t4, t6, 4
    slli t5, t3, 5
    or t4, t5, t3
    xor t4, a3, t5
    add t5, t6, t4
    add t6, t2, a2
    xor t6, t4, t5
    xor t5, t5, a3
    and t4, a2, t4
    addi a6, a0, 5
    addi a0, a6, 2    # a0 += 7
    addi a6, t2, 1
    addi t2, a6, 1    # t2 += 2
    addi a1, a0, 1
    addi a0, a1, 1    # a0 += 2
    addi a6, t1, 1
    addi t1, a6, 1    # t1 += 2
    addi a6, t0, 1    
    addi t0, a6, 1    # t0 += 2
    sd t4, 0(a0)
    sd t5, 16(a0)
    sd t6, 8(a0)
    bne t1, t3, L1    # t0 vs t3
    ret               # eof

.global workload2
workload2:
    xor a2, a1, a1    # a2 = 0
    addi a3, a2, 147  # a3 = 147
    slli a4, a3, 1    # a4 = 147 << 1
    or a2, a3, a4     # a2 = (147 << 1 + 147)
    addi a1, a0, 1000 # a1 = addr + 1000
    xor a3, a2, a2    # a3 = 0
J1:
    ld t0, 0(a0)
    addi t1, t0, 7
    bne a0, a1, J3
    beq a0, a0, J5
J2:
    addi t1, a0, 1
    addi a0, t1, 1
    beq a0, a0, J4
J3:
    add t0, a2, t1
    sd t0, 0(a0)  
    beq a0, a0, J2
J4:
    addi a3, a2, 123
    addi a2, a3, 456
    beq a0, a0, J1
J5:
    ret              # eof


.global workload3
workload3:
    xor  a1, a0, a0
    xor  t0, a1, a1
    addi t1, a1, 1
    addi t4, a0, 1016
R1:
    add t2, t1, t0
    sd t2, 0(a0)
    xor a2, a0, a0
    addi a1, a0, 1
    add a0, a1, a2
    xor a1, a0, a0
    add t0, t1, a1
    add t1, t2, a1
    bne t4, a0, R1
    ret              # eof
