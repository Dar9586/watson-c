#include "../libs.h"

String newString();

void putChar(String s, Int c);

void freeString(String s);

void encodeString(VM vm, Value value);

String fromCString(const char *buf);

String fromString(const char *buf, size_t len);

size_t getStringLength(String s);

char *getStringData(String s);
