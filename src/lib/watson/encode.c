#include "../libs.h"

void encodeInt(VM vm, Value value) {
    Uint val = value.u;
    char siz = 63;
    if (vm->error_code)return;
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
    if (vm->error_code)return;
    writeCommand(vm, Bnew);
    if (!value.b)return;
    writeCommand(vm, Bneg);
}

void encodeUint(VM vm, Value val) {
    if (vm->error_code)return;
    encodeInt(vm, val);
    if (val.i >= 0)return;
    writeCommand(vm, Itou);
}

void encodeFloat(VM vm, Value val) {
    if (vm->error_code)return;
    encodeInt(vm, val);
    writeCommand(vm, Itof);
}

int executeWatson(VM vm, Data data) {
    int ret;
    encodeWatson(vm, data);
    ret = vm->error_code;
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
