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

static struct fy_node *encodeYamlNum(struct fy_document *node, const char *format, Value v) {
    char val[100];
    snprintf(val, sizeof(val), format, v);
    return fy_node_create_scalar_copy(node, val, -1);
}

struct fy_node *encodeYamlInt(struct fy_document *node, Data data) {
    return encodeYamlNum(node, "%ld", val(data));
}

struct fy_node *encodeYamlUint(struct fy_document *node, Data data) {
    return encodeYamlNum(node, "%lu", val(data));
}

struct fy_node *encodeYamlFloat(struct fy_document *node, Data data) {
    return encodeYamlNum(node, "%lf", val(data));
}

static int arrayAdder(Data data, void *arg1, void *arg2) {
    struct fy_node *arr = arg1;
    struct fy_document *doc = arg2;
    fy_node_sequence_append(arr, encodeYaml(doc, data));
    return 0;
}

struct fy_node *encodeYamlArray(struct fy_document *node, Data data) {
    Array a = valArray(data);
    struct fy_node *arr = fy_node_create_sequence(node);
    iterateArray(a, arrayAdder, arr, node);
    return arr;
}

static int objectAdder(String key, Data value, void *arg1, void *arg2) {
    struct fy_node *obj = arg1;
    struct fy_document *doc = arg2;
    Data str = newDataString(key);
    fy_node_mapping_append(obj, encodeYamlString(doc, str),
                           encodeYaml(doc, value));
    shallowFreeData(str);
    return 0;
}

struct fy_node *encodeYamlObject(struct fy_document *node, Data data) {
    Object o = valObject(data);
    struct fy_node *obj = fy_node_create_mapping(node);
    iterateObject(o, objectAdder, obj, node);
    return obj;
}

int writeYamlDataToStream(Data data, FILE *fp) {
    struct fy_document *doc = fy_document_create(NULL);
    struct fy_node *root = encodeYaml(doc, data);
    fy_document_set_root(doc, root);
    int ret = fy_emit_document_to_fp(doc, FYECF_SORT_KEYS, fp);
    fy_document_destroy(doc);
    return ret;
}

int writeYamlDataToBuffer(Data data, char *buf, size_t len) {
    struct fy_document *doc = fy_document_create(NULL);
    struct fy_node *root = encodeYaml(doc, data);
    fy_document_set_root(doc, root);
    int ret = fy_emit_document_to_buffer(doc, FYECF_SORT_KEYS, buf, len) == -1 ? -1 : 0;
    fy_document_destroy(doc);
    return ret;
}

