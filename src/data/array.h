#include "../libs.h"
Array newArray();
void putArray(Array a, Data c);
void freeArray(Array a);
void encodeArray(VM vm, Value val);
void iterateArray(Array a, void (*foreach)(Data data, void *, void *),
                  void *arg1, void *arg2);
