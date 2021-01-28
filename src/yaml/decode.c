#include "../libs.h"

Data parseYaml(struct fy_node *node);
static regex_t floatRegex, intRegex, uintRegex;
static int8_t regexInitialized = 0;
void initRegex() {
  regcomp(&floatRegex, "^-?(0|[1-9][0-9]*)(\\.[0-9]*)?([eE][-+]?[0-9]+)?$",
          REG_NOSUB | REG_EXTENDED);
  regcomp(&intRegex, "^-?(0|[1-9][0-9]*)$", REG_NOSUB | REG_EXTENDED);
  regcomp(&uintRegex, "^(0|[1-9][0-9]*)$", REG_NOSUB | REG_EXTENDED);
  regexInitialized = 1;
}

Data processObject(struct fy_node *node) {
  Object o = newObject();
  int len = fy_node_mapping_item_count(node);
  int i;
  struct fy_node_pair *pair;
  Data key, val;
  for (i = 0; i < len; i++) {
    pair = fy_node_mapping_get_by_index(node, i);
    key = parseYaml(fy_node_pair_key(pair));
    val = parseYaml(fy_node_pair_value(pair));
    putObject(o, valString(key), val);
  }
  return newDataObject(o);
}

Data processArray(struct fy_node *node) {
  Array a = newArray();
  int len = fy_node_sequence_item_count(node);
  int i;
  for (i = 0; i < len; i++) {
    putArray(a, parseYaml(fy_node_sequence_get_by_index(node, i)));
  }
  return newDataArray(a);
}

char *dupString(const char *str, size_t len) {
  char *cpy = malloc(sizeof(char) * (len + 1));
  memcpy(cpy, str, sizeof(char) * len);
  cpy[len] = '\0';
  return cpy;
}

Data processScalar(struct fy_node *node) {
  size_t len;
  char *str;
  Value v;
  Data data = NULL;
  const char *ori = fy_node_get_scalar(node, &len);

  if (strncmp(ori, "null", len) == 0)
    return newDataNull();
  if (strncmp(ori, "true", len) == 0)
    return newDataBool(VM_TRUE);
  if (strncmp(ori, "false", len) == 0)
    return newDataBool(VM_FALSE);

  str = dupString(ori, len);

  if (regexec(&uintRegex, str, 0, NULL, 0) == 0) {
    sscanf(str, "%lu", &v.u);
    data = newDataUint(v.u);
  } else if (regexec(&intRegex, str, 0, NULL, 0) == 0) {
    sscanf(str, "%ld", &v.i);
    data = newDataInt(v.i);
  } else if (regexec(&floatRegex, str, 0, NULL, 0) == 0) {
    sscanf(str, "%lf", &v.f);
    data = newDataFloat(v.f);
  }
  free(str);
  return data == NULL ? newDataString(fromString(ori, len)) : data;
}

Data parseYaml(struct fy_node *node) {
  switch (fy_node_get_type(node)) {
  case FYNT_SCALAR:
    return processScalar(node);
  case FYNT_SEQUENCE:
    return processArray(node);
  case FYNT_MAPPING:
    return processObject(node);
  }
  return NULL;
}

Data yamlExecute(struct fy_document *fyd) {
  struct fy_node *root;
  Data d;
  if (fyd == NULL)
    exit(8);
  root = fy_document_root(fyd);
  if (!regexInitialized)
    initRegex();
  d = parseYaml(root);
  fy_document_destroy(fyd);
  return d;
}

Data parseYamlFromStream(FILE *fp) {
  struct fy_document *fyd = fy_document_build_from_fp(NULL, fp);
  return yamlExecute(fyd);
}
Data parseYamlFromString(const char *str, size_t len) {
  struct fy_document *fyd = fy_document_build_from_string(NULL, str, len);
  return yamlExecute(fyd);
}
