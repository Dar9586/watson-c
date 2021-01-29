#include "../libs.h"

Data parseJson(json_t *node);

Array parseArray(json_t *array) {
    Array a = newArray();
    size_t index;
    json_t *value;
    json_array_foreach(array, index, value) {
        putArray(a, parseJson(value));
    }
    return a;
}

Object parseObject(json_t *object) {
    Object o = newObject();
    const char *key;
    json_t *value;
    json_object_foreach(object, key, value) {
        putObject(o, fromCString(key), parseJson(value));
    }
    return o;
}

#define parseString(str)                                                       \
  fromString(json_string_value(str), json_string_length(str))

Data parseJson(json_t *node) {
    switch (json_typeof(node)) {
        case JSON_OBJECT:
            return newDataObject(parseObject(node));
        case JSON_ARRAY:
            return newDataArray(parseArray(node));
        case JSON_STRING:
            return newDataString(parseString(node));
        case JSON_INTEGER:
            return newDataInt(json_integer_value(node));
        case JSON_REAL:
            return newDataFloat(json_real_value(node));
        case JSON_TRUE:
            return newDataBool(VM_TRUE);
        case JSON_FALSE:
            return newDataBool(VM_FALSE);
        case JSON_NULL:
            return newDataNull();
    }
    return NULL;
}

Data jsonExecute(json_t *root, json_error_t error) {
    Data d;
    d = parseJson(root);
    json_decref(root);
    return d;
}

Data parseJsonFromStream(FILE *fp) {
    json_error_t error;
    json_t *var = json_loadf(fp, JSON_ALLOW_NUL | JSON_DECODE_ANY, &error);
    return jsonExecute(var, error);
}

Data parseJsonFromString(const char *str, size_t len) {
    json_error_t error;
    json_t *var = json_loadb(str, len, JSON_ALLOW_NUL | JSON_DECODE_ANY, &error);
    return jsonExecute(var, error);
}
