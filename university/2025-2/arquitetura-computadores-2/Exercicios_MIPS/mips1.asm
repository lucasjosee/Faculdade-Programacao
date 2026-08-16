# Programa 1

# Associações:
# a - $s0
# b - $s1
# c - $s2
# d - $s3
# x - $s4
# y - $s5

# inicio

addi $s0, $s0, 2
addi $s1, $s1, 3
addi $s2, $s2, 4
addi $s3, $s3, 5

add $t0, $s0, $s1
add $t1, $s2, $s3

sub $s4, $t0, $t1

sub $s5, $s0, $s1
add $s5, $s5, $s4

sub $s1, $s4, $s5 

# fim