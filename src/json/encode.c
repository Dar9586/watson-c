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
  Int ival = (Int)uval;
  return uval == ival ? json_integer(ival) : json_sprintf("%lu", uval);
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
