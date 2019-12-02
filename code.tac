.table

.code
main:
mov $2, 5
mov $0, $2
_While_Begin_0:
mov $3, 0
slt $4, $3, $0
brz _While_End_0, $4
print 'i'
println $0
mov $5, 5
mov $1, $5
_While_Begin_1:
mov $6, 0
slt $7, $6, $1
brz _While_End_1, $7
print 'j'
println $1
mov $8, 1
sub $9, $1, $8
mov $1, $9
jump _While_Begin_1
_While_End_1:
mov $10, 1
sub $11, $0, $10
mov $0, $11
jump _While_Begin_0
_While_End_0:
mov $12, 0
nop
