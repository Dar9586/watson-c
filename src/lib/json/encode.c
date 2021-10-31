#include "../libs.h"

static void arrayAdder(Data data, void *arg, void *arg2) {
    json_t *arr = arg;
    json_array_append(arr, encodeJson(data));
}

static void objectAdder(String key, Data value, void *arg, void *arg2) {
    json_t *obj = arg;
    json_object_setn(obj, getStringData(key), getStringLength(key),
                     encodeJson(value));
}

json_t *encodeJsonBool(Data data) {
    return json_boolean(valBool(data));
}

json_t *encodeJsonNull(Data data) {
    return json_null();
}

json_t *encodeJsonString(Data data) {
    String s = valString(data);
    return json_stringn(getStringData(s), getStringLength(s));
}

json_t *encodeJsonInt(Data data) {
    return json_integer(valInt(data));
}

json_t *encodeJsonUint(Data data) {
    Uint uval = valUint(data);
    return uval & SIGN_BIT ? json_sprintf("%lu", uval) : json_integer(uval);
}

json_t *encodeJsonFloat(Data data) {
    return json_real(valFloat(data));
}

json_t *encodeJsonArray(Data data) {
    Array a = valArray(data);
    json_t *arr = json_array();
    iterateArray(a, arrayAdder, arr, NULL);
    return arr;
}

json_t *encodeJsonObject(Data data) {
    Object o = valObject(data);
    json_t *obj = json_object();
    iterateObject(o, objectAdder, obj, NULL);
    return obj;
}

int writeJsonDataToStream(Data data, FILE *fp) {
    json_t *obj = encodeJson(data);
    int ret = json_dumpf(obj, fp, JSON_REAL_PRECISION(FLOAT_PRECISION_JSON) | JSON_ENCODE_ANY | JSON_COMPACT |
                                  JSON_ENSURE_ASCII | JSON_SORT_KEYS | JSON_ESCAPE_SLASH);
    json_decref(obj);
    return ret;
}

int writeJsonDataToBuffer(Data data, char *buf, size_t len) {
    json_t *obj = encodeJson(data);
    int ret = json_dumpb(obj, buf, len, JSON_REAL_PRECISION(FLOAT_PRECISION_JSON) | JSON_ENCODE_ANY | JSON_COMPACT |
                                        JSON_ENSURE_ASCII | JSON_SORT_KEYS | JSON_ESCAPE_SLASH);
    json_decref(obj);
    return ret;
}


