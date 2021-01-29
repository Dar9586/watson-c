#include"../libs.h"


Data parseWatsonFromStream(FILE *fp) {
    VM vm = newFileVM(LexerA, fp);
    int c;
    while ((c = fgetc(fp)) != EOF)parseCommand(vm, (char) c);
    Data d = pop(vm->stack);
    freeVM(vm);
    return d;
}

Data parseWatsonFromString(const char *str, size_t len) {
    VM vm = newBufferVM(LexerA, (char *) str, len);
    size_t i;
    for (i = 0; i < len; i++)parseCommand(vm, str[i]);
    Data d = pop(vm->stack);
    freeVM(vm);
    return d;
}

