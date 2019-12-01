.table
int a

.code
main:
mov $1, 10
mov a, $1
mov $2, 2
mul $3, a, $2
mov $0, $3
println $0
nop
