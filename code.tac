.table

.code
_printv:
mov $0, #0
mov $1, $0[0]
mov $1, *$1
mov $2, $0[0]
mov $5, 1
_While_Begin__0:
sleq $3, $5, $1
brz _While_End__0, $3
mov $4, $2[$5]
println $4
add $5, $5, 1
jump _While_Begin__0
_While_End__0:
return

_printvn:
mov $6, #0
mov $6, $6[0]
mov $6, *$6
println $6
return

_insNo:
mov $7, #0
mov $13, #1
mov $8, $7[0]
mov $8, *$8
add $8, $8, 2
mema $9, $8
sub $8, $8, 2
mov $10, $7[0]
mov $14, $8
add $8, $8, 1
mov $9[$8], $13
mov $9[0], $8
_While_Begin__1:
slt $12, 0, $14
brz _While_End__1, $12
mov $11, $10[$14]
mov $9[$14], $11
sub $14, $14, 1
jump _While_Begin__1
_While_End__1:
mov $7[0], $9
memf $10
return

main:
mema $15, 2
mema $16, 1
mov *$16, 0
mov $15[0], $16
mema $17, 1
mov *$17, 0
mov $15[1], $17
mov $18, 579
param $15
param $18
call _insNo, 2
mov $19, 2
mov $20, 3
add $21, $19, $20
param $15
param $21
call _insNo, 2
mov $22, 741
param $15
param $22
call _insNo, 2
param $15
call _printvn, 1
param $15
call _printv, 1
print '\n'
param $15
call _printv, 1
print '\n'
param $15
call _printvn, 1
mov $23, 0
nop
