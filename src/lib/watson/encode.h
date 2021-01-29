#include "../libs.h"

int encodeInt(VM vm, Value value);

int encodeNull(VM vm, Value v);

int encodeBool(VM vm, Value value);

int encodeUint(VM vm, Value val);

int encodeFloat(VM vm, Value val);

int writeWatsonDataToStream(Data data, FILE *fp);

int writeWatsonDataToBuffer(Data data, char *buf, size_t len);
