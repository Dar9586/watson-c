#include "../libs.h"

Object newObject();

void putObject(Object o, String name, Data data);

void freeObject(Object o);

int encodeObject(VM vm, Value val);

int iterateObject(Object a, int (*foreach)(String, Data, void *, void *),
                  void *arg1, void *arg2);
