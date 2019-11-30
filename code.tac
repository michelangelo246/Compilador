.table
char word[] = "Hello World"
int n = 11

.code
_imprime:
	mov $0, #0
	begin:
	slt $1, $0, 0
	brnz end, $1
	mov $2, &word
	sub $1, n, $0
	mov $2, $2[$1]
	print $2
	sub $0, $0, 1
	jump begin
	end:
	return

main:
	param n
	call _imprime, 1
