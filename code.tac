.table

.code
main:
mov $1, 0
mov $0, $1
_While_Begin_0:
mov $2, 1
mov $3, 1
seq $4, $2, $3
brz _While_End_0, $4
mov $5, 1
mov $0, $5
jump _While_Begin_0
_While_End_0:
mov $6, 0
nop
