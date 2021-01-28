#include "../libs.h"

void encodeInt(VM vm, Value value) {
  Uint val = value.u;
  char siz = 63;
  writeCommand(vm, Inew);
  if (val == 0)
    return;
  while ((val & (1UL << siz)) == 0)
    siz--;
  writeCommand(vm, Iinc);
  siz--;
  while (siz >= 0) {
    writeCommand(vm, Ishl);
    if (val & (1UL << siz))
      writeCommand(vm, Iinc);
    siz--;
  }
}

void encodeNull(VM vm, Value v) { writeCommand(vm, Nnew); }
void encodeBool(VM vm, Value value) {
  writeCommand(vm, Bnew);
  if (!value.b)return;
  writeCommand(vm, Bneg);
}
void encodeUint(VM vm, Value val) {
  encodeInt(vm, val);
  if(val.i >= 0)return;
  writeCommand(vm, Itou);
}
void encodeFloat(VM vm, Value val) {
  encodeInt(vm, val);
  writeCommand(vm, Itof);
}
