#include "../libs.h"

#define switchMode(vm) vm->lexer = (vm->lexer == LexerA ? LexerS : LexerA)

struct command {
  CommandCode commandName;
  void (*commandFunction)(VM vm);
  char commandChar[LEXER_COUNT];
};

static struct command commands[] = {
    {Inew, vmInew, {'B', 'S'}}, {Iinc, vmIinc, {'u', 'h'}},
    {Ishl, vmIshl, {'b', 'a'}}, {Iadd, vmIadd, {'a', 'k'}},
    {Ineg, vmIneg, {'A', 'r'}}, {Isht, vmIsht, {'e', 'A'}},
    {Itof, vmItof, {'i', 'z'}}, {Itou, vmItou, {'\'', 'i'}},
    {Finf, vmFinf, {'q', 'm'}}, {Fnan, vmFnan, {'t', 'b'}},
    {Fneg, vmFneg, {'p', 'u'}}, {Snew, vmSnew, {'?', '$'}},
    {Sadd, vmSadd, {'!', '-'}}, {Onew, vmOnew, {'~', '+'}},
    {Oadd, vmOadd, {'M', 'g'}}, {Anew, vmAnew, {'@', 'v'}},
    {Aadd, vmAadd, {'s', '?'}}, {Bnew, vmBnew, {'z', '^'}},
    {Bneg, vmBneg, {'o', '!'}}, {Nnew, vmNnew, {'.', 'y'}},
    {Gdup, vmGdup, {'E', '/'}}, {Gpop, vmGpop, {'#', 'e'}},
    {Gswp, vmGswp, {'%', ':'}}};

VM newVM(Lexer lexer) {
  VM v = malloc(sizeof(struct vm));
  v->lexer = lexer;
  v->stack = newStack();
  return v;
}

void parseCommandLexar(VM vm, char c) {
  int i;
  Lexer l = vm->lexer;
  for (i = 0; i < COMMAND_COUNT; i++) {
    if (commands[i].commandChar[l] == c)
      commands[i].commandFunction(vm);
  }
}
void parseCommand(VM vm, char c) {
  parseCommandLexar(vm, c);
  if (c == commands[Snew].commandChar[vm->lexer])
    switchMode(vm);
}

void freeVM(VM vm) {
  freeStack(vm->stack);
  free(vm);
}

void writeCommand(VM vm, CommandCode com) {
  putchar(commands[com].commandChar[vm->lexer]);
  if (com == Snew)
    switchMode(vm);
}
