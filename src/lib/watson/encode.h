#include "../libs.h"

void encodeInt(VM vm, Value value);

void encodeNull(VM vm, Value v);

void encodeBool(VM vm, Value value);

void encodeUint(VM vm, Value val);

void encodeFloat(VM vm, Value val);

int writeWatsonDataToStream(Data data, FILE *fp);

int writeWatsonDataToBuffer(Data data, char *buf, size_t len);
