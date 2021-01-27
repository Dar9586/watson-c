#include "../libs.h"

struct fy_node *encodeYamlBool(struct fy_document *node, Data data) {
  Bool b = valBool(data);
  return b ? fy_node_create_scalar(node, "true", 4)
           : fy_node_create_scalar(node, "false", 5);
}
struct fy_node *encodeYamlNull(struct fy_document *node, Data data) {
  return fy_node_create_scalar(node, "null", 4);
}
struct fy_node *encodeYamlString(struct fy_document *node, Data data) {
  String s = valString(data);
  return fy_node_create_scalar(node, getStringData(s), getStringLength(s));
}
struct fy_node *encodeYamlInt(struct fy_document *node, Data data) {
  char val[30], *dup;
  size_t len;
  sprintf(val, "%ld", valInt(data));
  len = strlen(val);
  dup = malloc(sizeof(char) * len);
  memcpy(dup, val, len);
  return fy_node_create_scalar(node, dup, len);
}
struct fy_node *encodeYamlUint(struct fy_document *node, Data data) {
  char val[30], *dup;
  size_t len;
  sprintf(val, "%lu", valUint(data));
  len = strlen(val);
  dup = malloc(sizeof(char) * len);
  memcpy(dup, val, len);
  return fy_node_create_scalar(node, dup, len);
}
struct fy_node *encodeYamlFloat(struct fy_document *node, Data data) {
  char val[100], *dup;
  size_t len;
  sprintf(val, "%lf", valFloat(data));
  len = strlen(val);
  dup = malloc(sizeof(char) * len);
  memcpy(dup, val, len);
  return fy_node_create_scalar(node, dup, len);
}

static void arrayAdder(Data data, void *arg1, void *arg2) {
  struct fy_node *arr = arg1;
  struct fy_document *doc = arg2;
  fy_node_sequence_append(arr, encodeYaml(doc, data));
}

struct fy_node *encodeYamlArray(struct fy_document *node, Data data) {
  Array a = valArray(data);
  struct fy_node *arr = fy_node_create_sequence(node);
  iterateArray(a, arrayAdder, arr, node);
  return arr;
}
static void objectAdder(String key, Data value, void *arg1, void *arg2) {
  struct fy_node *obj = arg1;
  struct fy_document *doc = arg2;
  fy_node_mapping_append(obj, encodeYaml(doc, newDataString(key)),
                         encodeYaml(doc, value));
}

struct fy_node *encodeYamlObject(struct fy_document *node, Data data) {
  Object o = valObject(data);
  struct fy_node *obj = fy_node_create_mapping(node);
  iterateObject(o, objectAdder, obj, node);
  return obj;
}
