#include "../libs.h"

void vmInew(VM vm) { push(vm->stack, newDataInt(0)); }
void vmIinc(VM vm) {
  Data x = top(vm->stack);
  updateDataInt(x, valInt(x) + 1);
}
void vmIshl(VM vm) {
  Data x = top(vm->stack);
  updateDataInt(x, valInt(x) << 1);
}
void vmIadd(VM vm) {
  Data x = pop(vm->stack);
  Data y = pop(vm->stack);
  updateDataInt(x, valInt(x) + valInt(y));
  freeData(y);
  push(vm->stack, x);
}
void vmIneg(VM vm) {
  Data x = top(vm->stack);
  updateDataInt(x, -valInt(x));
}
void vmIsht(VM vm) {
  Data y = pop(vm->stack);
  Data x = pop(vm->stack);
  updateDataInt(x, valInt(x) << valInt(y));
  freeData(y);
  push(vm->stack, x);
}
void vmItof(VM vm) {
  Data x = top(vm->stack);
  updateType(x, FloatType);
}
void vmItou(VM vm) {
  Data x = top(vm->stack);
  updateType(x, UintType);
}
void vmFinf(VM vm) { push(vm->stack, newDataFloat(INF)); }
void vmFnan(VM vm) { push(vm->stack, newDataFloat(NAN)); }
void vmFneg(VM vm) {
  Data x = top(vm->stack);
  updateDataFloat(x, -valFloat(x));
}
void vmSnew(VM vm) { push(vm->stack, newDataString(newString())); }
void vmSadd(VM vm) {
  Data val = pop(vm->stack);
  Data str = pop(vm->stack);
  putChar(valString(str), valInt(val));
  freeData(val);
  push(vm->stack, str);
}
void vmOnew(VM vm) { push(vm->stack, newDataObject(newObject())); }
void vmOadd(VM vm) {
  Data val = pop(vm->stack); /*control of val passed to arr*/
  Data str = pop(vm->stack); /*control of str passed to arr*/
  Data obj = pop(vm->stack);
  putObject(valObject(obj), valString(str), val);
  push(vm->stack, obj);
}
void vmAnew(VM vm) { push(vm->stack, newDataArray(newArray())); }
void vmAadd(VM vm) {
  Data val = pop(vm->stack); /*control of val passed to arr*/
  Data arr = pop(vm->stack);
  putArray(valArray(arr), val);
  push(vm->stack, arr);
}
void vmBnew(VM vm) { push(vm->stack, newDataBool(VM_FALSE));  }
void vmBneg(VM vm) {
  Data val = top(vm->stack);
  updateDataBool(val, !valBool(val));
}
void vmNnew(VM vm) { push(vm->stack, newDataNull()); }
void vmGdup(VM vm) {
  Data d = pop(vm->stack);
  push(vm->stack, d);
  push(vm->stack, d);
}
void vmGpop(VM vm) { freeData(pop(vm->stack)); }
void vmGswp(VM vm) {
  Data d1 = pop(vm->stack);
  Data d2 = pop(vm->stack);
  push(vm->stack, d1);
  push(vm->stack, d2);
}