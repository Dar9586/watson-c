#include"../libs.h"

Data parseWatsonFromStream(FILE*fp){
    VM vm=newVM(LexerA);
    int c;
    while((c=fgetc(fp))!=EOF)parseCommand(vm,c);
    return pop(vm->stack);
}
Data parseWatsonFromString(const char*str,size_t len){
    VM vm=newVM(LexerA);
    size_t i;
    for(i=0;i<len;i++)parseCommand(vm,str[i]);
    return pop(vm->stack);
}

