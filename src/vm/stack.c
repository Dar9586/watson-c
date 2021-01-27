
#include "../libs.h"

struct element {
  Data data;
  struct element *next;
};
struct stack {
  struct element *top;
  size_t size;
};

Stack newStack() {
  Stack stack = malloc(sizeof(struct stack));
  stack->top = NULL;
  stack->size = 0;
  return stack;
}

void freeStack(Stack stack) {
  while (stack->size) {
    freeData(pop(stack));
  }
  free(stack);
}

int isEmpty(Stack stack) { return stack->size == 0; }

void push(Stack stack, Data data) {
  struct element *el = malloc(sizeof(struct element));
  el->data = data;
  el->next = stack->top;
  stack->top = el;
  stack->size++;
}
Data pop(Stack stack) {
  struct element *el = stack->top;
  Data data = el->data;
  stack->top = el->next;
  stack->size--;
  free(el);
  return data;
}
Data top(Stack stack) {
  struct element *el = stack->top;
  return el->data;
}

