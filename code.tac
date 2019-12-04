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
mov $0, #0
mov $0, $0[0]
mov $0, *$0
println $0
return

_printa:
mov $0, #0
mov $1, $0[1]
mov $1, *$1
mul $1, $1, 2
mov $2, $0[1]
mov $5, 1
_While_Begin__1:
sleq $3, $5, $1
brz _While_End__1, $3
mov $4, $2[$5]
print $4
print ' '
add $5, $5, 1
mov $4, $2[$5]
println $4
add $5, $5, 1
jump _While_Begin__1
_While_End__1:
return

_insNo:
mov $0, #0
mov $6, #1
mov $1, $0[0]
mov $1, *$1
add $1, $1, 2
mema $2, $1
sub $1, $1, 2
mov $3, $0[0]
mov $7, $1
add $1, $1, 1
mov $2[$1], $6
mov $2[0], $1
_While_Begin__2:
slt $5, 0, $7
brz _While_End__2, $5
mov $4, $3[$7]
mov $2[$7], $4
sub $7, $7, 1
jump _While_Begin__2
_While_End__2:
mov $0[0], $2
memf $3
return

_insAresta:
mov $0, #0
mov $1, #1
mov $7, #2
mov $2, $0[1]
mov $2, *$2
mul $2, $2, 2
add $2, $2, 3
mema $3, $2
sub $2, $2, 3
div $2, $2, 2
mov $4, $0[1]
mov $8, $2
mul $8, $8, 2
add $2, $8, 1
mov $3[$2], $1
add $2, $2, 1
mov $3[$2], $7
div $2, $2, 2
mov $3[0], $2
_While_Begin__3:
slt $5, 0, $8
brz _While_End__3, $5
mov $6, $4[$8]
mov $3[$8], $6
sub $8, $8, 1
jump _While_Begin__3
_While_End__3:
mov $0[1], $3
memf $4
return

_getGrauIn:
mov $0, #0
mov $1, #1
mov $2, $0[1]
mov $2, *$2
mul $2, $2, 2
sub $2, $2, 0
mov $3, $0[1]
mov $4, 0
_While_Begin__4:
slt $5, 0, $2
brz _While_End__4, $5
mov $6, $3[$2]
seq $6, $6, $1
brz _While_Check_4, $6
add $4, $4, 1
_While_Check_4:
sub $2, $2, 2
jump _While_Begin__4
_While_End__4:
return $4

_getGrauOut:
mov $0, #0
mov $1, #1
mov $2, $0[1]
mov $2, *$2
mul $2, $2, 2
sub $2, $2, 1
mov $3, $0[1]
mov $4, 0
_While_Begin__5:
slt $5, 0, $2
brz _While_End__5, $5
mov $6, $3[$2]
seq $6, $6, $1
brz _While_Check_5, $6
add $4, $4, 1
_While_Check_5:
sub $2, $2, 2
jump _While_Begin__5
_While_End__5:
return $4

main:
mema $0, 2
mema $1, 1
mov *$1, 0
mov $0[0], $1
mema $2, 1
mov *$2, 0
mov $0[1], $2
mema $3, 2
mema $4, 1
mov *$4, 0
mov $3[0], $4
mema $5, 1
mov *$5, 0
mov $3[1], $5
mov $7, 2
mov $8, 3
param $0
param $7
param $8
call _insAresta, 3
mov $9, 2
mov $10, 5
param $0
param $9
param $10
call _insAresta, 3
mov $11, 2
mov $12, 6
param $0
param $11
param $12
call _insAresta, 3
mov $13, 2
mov $14, 5
param $0
param $13
param $14
call _insAresta, 3
mov $15, 3
mov $16, 5
param $0
param $15
param $16
call _insAresta, 3
mov $17, 4
mov $18, 5
param $0
param $17
param $18
call _insAresta, 3
mov $19, 5
mov $20, 5
param $0
param $19
param $20
call _insAresta, 3
mov $21, 3
mov $22, 5
param $0
param $21
param $22
call _insAresta, 3
mov $23, 3
mov $24, 6
param $0
param $23
param $24
call _insAresta, 3
mov $25, 6
param $0
param $25
call _getGrauIn, 2
pop $26
println $26
mov $27, 5
param $0
param $27
call _getGrauIn, 2
pop $28
println $28
mov $29, 3
param $0
param $29
call _getGrauIn, 2
pop $30
println $30
mov $31, 2
param $0
param $31
call _getGrauOut, 2
pop $32
println $32
mov $33, 3
param $0
param $33
call _getGrauOut, 2
pop $34
println $34
mov $35, 4
param $0
param $35
call _getGrauOut, 2
pop $36
println $36
mov $37, 10
mov $6, $37
_While_Begin_0:
mov $38, 0
slt $39, $38, $6
brz _While_End_0, $39
print 'H'
print 'e'
print 'l'
print 'l'
print 'o'
print ' '
println $6
print '\n'
mov $40, 1
sub $41, $6, $40
mov $6, $41
jump _While_Begin_0
_While_End_0:
nop
