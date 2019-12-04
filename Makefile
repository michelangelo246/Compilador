all: TestGOL

clean:
	rm -f *.o
	rm -f *.png
	rm -f *.pdf
	rm -f *.dot
	rm -f *.tac
	rm Lexer.c
	rm Parser.c

TestGOL: Syntactic.o Lexer.o Parser.o Printer.o Test.o
	#@echo "Linking TestGOL..."
	gcc -g -W -Wall Syntactic.o Lexer.o Parser.o Printer.o Test.o -o parser
	rm *.o
	rm -f *.png
	rm -f *.pdf
	rm -f *.dot
	rm -f *.tac
	rm Lexer.c
	rm Parser.c

Syntactic.o: Syntactic.c Syntactic.h
	gcc -g -W -Wall -c Syntactic.c

Lexer.c: GOL.l
	flex -PGOL -o Lexer.c GOL.l

Parser.c: GOL.y
	bison -t -pGOL GOL.y -o Parser.c

Lexer.o: Lexer.c Parser.h
	gcc -g -W -Wall -c Lexer.c 

Parser.o: Parser.c Syntactic.h
	gcc -g -W -Wall -c Parser.c

Printer.o: Printer.c Printer.h Syntactic.h
	gcc -g -W -Wall -c Printer.c

Test.o: Test.c Parser.h Printer.h Syntactic.h
	gcc -g -W -Wall -c Test.c