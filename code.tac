.table
int num
float num2

.code
func:
mov $0, 2
mov $1, 3.500000
mov $2, 2
inttofl $2, $2
div $1, $1, $2
inttofl $0, $0
add $0, $0, $1
minus $0, $0
print $0
return $0
main:
mov $3, 1
call func
nop
