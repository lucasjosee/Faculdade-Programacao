# Programa 4

# Associações:
# x - $s0
# y - $s1
# z - $s2

# inicio

addi $s0, $s0, 3
addi $s1, $s1, 4

sll $t0, $s0, 4
sub $t0, $t0, $s0

sll $t1, $s1, 6
add $t1, $t1, $s1
add $t1, $t1, $s1
add $t1, $t1, $s1

add $t2, $t0, $t1

sll $s2, $t2, 2

# fim