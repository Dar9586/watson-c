#include "../libs.h"

struct element {
    String name;
    Data data;
    struct element *next;
};

struct object {
    struct element *head, *tail;
    size_t length;
};

Object newObject() {
    Object o = malloc(sizeof(struct object));
    o->head = NULL;
    o->tail = NULL;
    o->length = 0;
    return o;
}

void putObject(Object o, String name, Data data) {
    struct element *el = malloc(sizeof(struct element));
    el->name = name;
    el->data = data;
    el->next = NULL;

    if (o->length == 0) {
        o->head = el;
    } else {
        o->tail->next = el;
    }

    o->tail = el;
    o->length++;
}

void freeObject(Object o) {
    struct element *el = o->head, *last;
    while (el) {
        last = el;
        el = el->next;
        freeString(last->name);
        deepFreeData(last->data);
        free(last);
    }
    free(o);
}

void encodeObjectIterate(String key, Data value, void *arg1, void *arg2) {
    VM vm = arg1;
    Value v;
    v.s = key;
    encodeString(vm, v);
    encodeWatson(vm, value);
    writeCommand(vm, Oadd);
}

void encodeObject(VM vm, Value val) {
    Object a = val.o;
    if (vm->error_code)return;
    writeCommand(vm, Onew);
    return iterateObject(a, encodeObjectIterate, vm, NULL);
}

void iterateObject(Object a, void (*foreach)(String, Data, void *, void *),
                   void *arg1, void *arg2) {
    struct element *el = a->head;
    VM vm = arg1;
    while (el) {
        if (vm->error_code)return;
        foreach(el->name, el->data, arg1, arg2);
        el = el->next;
    }
}
