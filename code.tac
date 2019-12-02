.table

.code
main:
mema $0, 2
mema $1, 1
mov *$1, 0
mov $0[0], $1
mema $2, 1
mov *$2, 0
mov $0[1], $2
mov $3, 32
mov $4, $3
mov $5, $0[0]
mov $5, *$5
add $5, $5, 2
mema $6, $5
sub $5, $5, 2
mov $7, $0[0]
mov $8, $5
add $5, $5, 1
mov $6[$5], $4
mov $6[0], $5
_While_Begin__0:
slt $9, 0, $8
brz _While_End__0, $9
mov $10, $7[$8]
mov $6[$8], $10
sub $8, $8, 1
jump _While_Begin__0
_While_End__0:
mov $0[0], $6
memf $7
nop
