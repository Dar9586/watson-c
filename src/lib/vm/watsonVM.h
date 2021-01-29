#include "../libs.h"

VM newBufferVM(Lexer lexer, char *buf, size_t len);

VM newFileVM(Lexer lexer, FILE *fp);

Data vmParse(VM vm, const char *str);

int writeCommand(VM vm, CommandCode com);

void parseCommand(VM vm, char c);

void freeVM(VM vm);
