#include "../libs.h"

int encodeInt(VM vm, Value value) {
    Uint val = value.u;
    char siz = 63;
    if (writeCommand(vm, Inew))return -1;
    if (val == 0)
        return 0;
    while ((val & (1UL << siz)) == 0)
        siz--;
    if (writeCommand(vm, Iinc))return -1;
    siz--;
    while (siz >= 0) {
        if (writeCommand(vm, Ishl))return -1;
        if (val & (1UL << siz))
            if (writeCommand(vm, Iinc))return -1;
        siz--;
    }
    return 0;
}

int encodeNull(VM vm, Value v) { if (writeCommand(vm, Nnew))return -1; }

int encodeBool(VM vm, Value value) {
    if (writeCommand(vm, Bnew))return -1;
    if (!value.b)return 0;
    if (writeCommand(vm, Bneg))return -1;
    return 0;
}

int encodeUint(VM vm, Value val) {
    encodeInt(vm, val);
    if (val.i >= 0)return 0;
    if (writeCommand(vm, Itou))return -1;
    return 0;
}

int encodeFloat(VM vm, Value val) {
    encodeInt(vm, val);
    if (writeCommand(vm, Itof))return -1;
    return 0;
}

int executeWatson(VM vm, Data data) {
    int ret = encodeWatson(vm, data);
    freeVM(vm);
    return ret;
}

int writeWatsonDataToStream(Data data, FILE *fp) {
    VM vm = newFileVM(LexerA, fp);
    return executeWatson(vm, data);
}

int writeWatsonDataToBuffer(Data data, char *buf, size_t len) {
    VM vm = newBufferVM(LexerA, buf, len);
    return executeWatson(vm, data);
}
