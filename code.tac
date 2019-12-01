.table

.code
f2:
mov $0, #0
mov $1, 10
add $2, $0, $1
return $2
f1:
mov $3, #0
mov $4, 2
mul $5, $3, $4
param $5
call f2, 1
pop $6
return $6
main:
mov $7, 10
param $7
call f1, 1
pop $8
mov $9, $8
println $9
nop
