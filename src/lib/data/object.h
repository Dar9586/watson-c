#include "../libs.h"

Object newObject();

void putObject(Object o, String name, Data data);

void freeObject(Object o);

void encodeObject(VM vm, Value val);

void iterateObject(Object a, void (*foreach)(String, Data, void *, void *),
                   void *arg1, void *arg2);
