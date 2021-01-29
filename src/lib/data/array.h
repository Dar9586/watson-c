#include "../libs.h"

Array newArray();

void putArray(Array a, Data c);

void freeArray(Array a);

int encodeArray(VM vm, Value val);

int iterateArray(Array a, int (*foreach)(Data data, void *, void *),
                 void *arg1, void *arg2);
