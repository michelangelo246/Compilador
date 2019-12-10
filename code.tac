
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

_graphNeig:
mov $0, #0
mov $1, #1
mema $2, 2
mema $3, 1
mov *$3, 0
mov $2[0], $3
mema $4, 1
mov *$4, 0
mov $2[1], $4
mov $5, $0
mov $6, $5[1]
mov $6, *$6
mul $6, $6, 2
mov $7, $5[1]
mov $8, 1
_While_Begin__6:
sleq $9, $8, $6
brz _While_End__6, $9
mov $10, $7[$8]
add $8, $8, 1
mov $11, $7[$8]
seq $12, $10, $1
brz _NaoTem_6, $12
param $2
param $11
call _insNo, 2
jump _End_6
_NaoTem_6:
seq $12, $11, $1
brz _End_6, $12
param $2
param $10
call _insNo, 2
_End_6:
add $8, $8, 1
jump _While_Begin__6
_While_End__6:
return $2

_printd:
print 'd'
print 'i'
print 'g'
print 'r'
print 'a'
print 'p'
print 'h'
print '{'
mov $0, #0
mov $1, $0[0]
mov $1, *$1
mov $2, $0[0]
mov $5, 1
_While_Begin__7:
sleq $3, $5, $1
brz _While_End__7, $3
mov $4, $2[$5]
print $4
print ';'
add $5, $5, 1
jump _While_Begin__7
_While_End__7:
mov $6, #0
mov $7, $6[1]
mov $7, *$7
mul $7, $7, 2
mov $8, $6[1]
mov $11, 1
_While_Begin__8:
sleq $9, $11, $7
brz _While_End__8, $9
mov $10, $8[$11]
print $10
print '-'
print '>'
print ' '
add $11, $11, 1
mov $10, $8[$11]
println $10
print ';'
add $11, $11, 1
jump _While_Begin__8
_While_End__8:
print '}'
return

main:
mema $0, 2
mema $1, 1
mov *$1, 0
mov $0[0], $1
mema $2, 1
mov *$2, 0
mov $0[1], $2
mov $3, 0
mov $4, 1
param $0
param $3
param $4
call _insAresta, 3
mov $5, 0
mov $6, 2
param $0
param $5
param $6
call _insAresta, 3
mov $7, 0
mov $8, 3
param $0
param $7
param $8
call _insAresta, 3
param $0
call _printd, 1
mov $9, 0

nop
