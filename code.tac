.table

.code
main:
mov $0, 0
mov $1, $0
mema $3, 2
mema $4, 1
mov *$4, 0
mov $3[0], $4
mema $5, 1
mov *$5, 0
mov $3[1], $5
mov $6, $3[0]
mov $6, *$6
mov $7, $3[0]
mov $8, 0
_While_Begin__0:
sleq $9, $8, $6
brz _While_End__0, $9
mov $10, $7[$8]
println $10
add $8, $8, 1
jump _While_Begin__0
_While_End__0:
mov $11, 0
nop
