#include "../libs.h"

VM newVM(Lexer lexer);
Data vmParse(VM vm, const char *str);
void writeCommand(VM vm, CommandCode com);
void parseCommand(VM vm, char c);
