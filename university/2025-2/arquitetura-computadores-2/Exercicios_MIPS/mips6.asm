# Programa 6

# Associações:
# x - $s0
# y - $s1
# z - $s2

# inicio

addi $s0, $zero, 0x7FFFFFFF
addi $s1, $zero, 300000

sll $t0, $s1, 2

sub $s2, $s0, $s1

# fim