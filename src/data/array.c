#include "../libs.h"

struct element {
  Data data;
  struct element *next;
};

struct array {
  struct element *head, *tail;
  size_t length;
};

Array newArray() {
  Array a = malloc(sizeof(struct array));
  a->head = NULL;
  a->tail = NULL;
  a->length = 0;
  return a;
}

void putArray(Array a, Data c) {
  struct element *el = malloc(sizeof(struct element));
  el->data = c;
  el->next = NULL;

  if (a->length == 0) {
    a->head = el;
  } else {
    a->tail->next = el;
  }

  a->tail = el;
  a->length++;
}

void freeArray(Array a) {
  struct element *el = a->head, *last;
  while(el) {
    last = el;
    el = el->next;
    free(last);
  }
  free(a);
}
void iterateArray(Array a, void (*foreach)(Data data, void *, void *),
                  void *arg1, void *arg2) {
  struct element *el = a->head;
  while (el) {
    foreach (el->data, arg1, arg2);
    el = el->next;
  }
}

void encodeArrayIterate(Data data,void*arg1,void*arg2){
  VM vm=arg1;
  encodeWatson(vm, data);
  writeCommand(vm, Aadd);
}

void encodeArray(VM vm, Value val) {
  Array a = val.a;
  writeCommand(vm, Anew);
  iterateArray(a,encodeArrayIterate,vm,NULL);
}