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

_printa:
mov $7, #0
mov $8, $7[1]
mov $8, *$8
mul $8, $8, 2
mov $9, $7[1]
mov $12, 1
_While_Begin__1:
sleq $10, $12, $8
brz _While_End__1, $10
mov $11, $9[$12]
print $11
print ' '
add $12, $12, 1
mov $11, $9[$12]
println $11
add $12, $12, 1
jump _While_Begin__1
_While_End__1:
return

_insNo:
mov $13, #0
mov $19, #1
mov $14, $13[0]
mov $14, *$14
add $14, $14, 2
mema $15, $14
sub $14, $14, 2
mov $16, $13[0]
mov $20, $14
add $14, $14, 1
mov $15[$14], $19
mov $15[0], $14
_While_Begin__2:
slt $18, 0, $20
brz _While_End__2, $18
mov $17, $16[$20]
mov $15[$20], $17
sub $20, $20, 1
jump _While_Begin__2
_While_End__2:
mov $13[0], $15
memf $16
return

_insAresta:
mov $21, #0
mov $22, #1
mov $28, #2
mov $23, $21[1]
mov $23, *$23
mul $23, $23, 2
add $23, $23, 3
mema $24, $23
sub $23, $23, 3
div $23, $23, 2
mov $25, $21[1]
mov $29, $23
mul $29, $29, 2
add $23, $29, 1
mov $24[$23], $22
add $23, $23, 1
mov $24[$23], $28
div $23, $23, 2
mov $24[0], $23
_While_Begin__3:
slt $26, 0, $29
brz _While_End__3, $26
mov $27, $25[$29]
mov $24[$29], $27
sub $29, $29, 1
jump _While_Begin__3
_While_End__3:
mov $21[1], $24
memf $25
return

main:
mema $30, 2
mema $31, 1
mov *$31, 0
mov $30[0], $31
mema $32, 1
mov *$32, 0
mov $30[1], $32
mema $33, 2
mema $34, 1
mov *$34, 0
mov $33[0], $34
mema $35, 1
mov *$35, 0
mov $33[1], $35
mema $36, 2
mema $37, 1
mov *$37, 0
mov $36[0], $37
mema $38, 1
mov *$38, 0
mov $36[1], $38
mov $39, 12
mov $40, 24
param $30
param $39
param $40
call _insAresta, 3
mov $41, 52
mov $42, 43
param $30
param $41
param $42
call _insAresta, 3
mov $43, 63
mov $44, 47
param $30
param $43
param $44
call _insAresta, 3
mov $45, 1
mov $46, 2
param $33
param $45
param $46
call _insAresta, 3
mov $47, 4
mov $48, 5
param $36
param $47
param $48
call _insAresta, 3
mov $49, 3
mov $50, 4
param $33
param $49
param $50
call _insAresta, 3
param $30
call _printa, 1
param $33
call _printa, 1
param $36
call _printa, 1
nop
