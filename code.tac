.table

.code
main:
mov $1, 11
mov $0, $1
mov $2, 10
slt $3, $0, $2
brz _If_End_0, $3
mov $4, 0
seq $5, $0, $4
brz _If_End_1, $5
mov $6, 100
mov $0, $6
_If_End_1:
not $5, $5
brz _If_End2_1, $5
mov $7, 99
mov $0, $7
_If_End2_1:
_If_End_0:
not $3, $3
brz _If_End2_0, $3
mov $8, 90
mov $0, $8
_If_End2_0:
println $0
mov $9, 0
nop
