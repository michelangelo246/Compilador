/**	Michelangelo da R. Machado - 14/0156089 **/

#ifndef PRINTER_HEADER
#define PRINTER_HEADER

#include "Syntactic.h"

#define BUFFER_INITIAL 2000

char *showTrans_Unit(No p);

void shTree(No p, int);

void shInteger(Integer n);
void shDouble(Double d);
void shString(String s);
void shIdent(String s);

char* printType(int kind, int modo);

void bufAppendS(const char *s);
void bufAppendC(const char c);
void bufReset(void);
void resizeBuffer(void);

#endif

