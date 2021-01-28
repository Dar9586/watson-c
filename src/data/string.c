#include "../libs.h"

#define calculateNewSize(oldSize) ((oldSize) + ((oldSize) / 2))
#define INITIAL_SIZE 10

struct string {
  char *data;
  size_t capacity;
  size_t length;
};

size_t getStringLength(String s) { return s->length; }

char *getStringData(String s) { return s->data; }

String fromString(const char *buf, size_t len) {
  String s = malloc(sizeof(struct string));
  s->data = malloc(sizeof(char) * len);
  s->capacity = len;
  s->length = len;
  memcpy(s->data, buf, sizeof(char) * len);
  return s;
}

String fromCString(const char *buf) {
  size_t len = strlen(buf);
  String s = malloc(sizeof(struct string));
  s->data = malloc(sizeof(char) * len);
  s->capacity = len;
  s->length = len;
  memcpy(s->data, buf, sizeof(char) * len);
  return s;
}

String newString() {
  String s = malloc(sizeof(struct string));
  s->data = malloc(sizeof(char) * INITIAL_SIZE);
  s->capacity = INITIAL_SIZE;
  s->length = 0;
  return s;
}

void growString(String s) {
  s->capacity = calculateNewSize(s->capacity);
  s->data = realloc(s->data, sizeof(char) * s->capacity);
  if (s->data == NULL) {
    fprintf(stderr, "Unable to grow string\n");
    exit(1);
  }
}

void putChar(String s, Int val) {
  char c = val & 0xFF; /*probably useless*/
  if (s->length == s->capacity) {
    growString(s);
  }
  s->data[s->length++] = c;
}

void freeString(String s) {
  free(s->data);
  free(s);
}

void encodeString(VM vm, Value value) {
  String str = value.s;
  size_t i;
  writeCommand(vm, Snew);
  for (i = 0; i < str->length; i++) {
    Value v;
    v.u = str->data[i];
    encodeInt(vm, v);
    writeCommand(vm, Sadd);
  }
}
