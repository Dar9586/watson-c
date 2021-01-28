
#include "../libs.h"

struct vmData {
  Value val;
  DataType type;
};
struct Master {
  DataType type;
  json_t *(*encodeJson)(Data);
  struct fy_node *(*encodeYaml)(struct fy_document *, Data);
  void (*encodeWatson)(VM, Value);
};
const struct Master dataMap[VAR_TYPE_COUNT]={
    {IntType   ,encodeJsonInt   ,encodeYamlInt   ,encodeInt   },
    {UintType  ,encodeJsonUint  ,encodeYamlUint  ,encodeUint  },
    {FloatType ,encodeJsonFloat ,encodeYamlFloat ,encodeFloat },
    {StringType,encodeJsonString,encodeYamlString,encodeString},
    {NullType  ,encodeJsonNull  ,encodeYamlNull  ,encodeNull  },
    {BoolType  ,encodeJsonBool  ,encodeYamlBool  ,encodeBool  },
    {ObjectType,encodeJsonObject,encodeYamlObject,encodeObject},
    {ArrayType ,encodeJsonArray ,encodeYamlArray ,encodeArray }
};

Int valInt(Data data) { return data->val.i; }
Uint valUint(Data data) { return data->val.u; }
Float valFloat(Data data) { return data->val.f; }
String valString(Data data) {return data->val.s;}
Bool valBool(Data data) { return data->val.b; }
Object valObject(Data data) {return data->val.o;}
Array valArray(Data data) {return data->val.a;}
Value val(Data data) { return data->val; }

Data newData(Value data, DataType type) {
  Data x = (Data)malloc(sizeof(struct vmData));
  x->val = data;
  x->type = type;
  return x;
}

Data newDataInt(Int x) {
  Value v;
  v.i = x;
  return newData(v, IntType);
}
Data newDataUint(Uint x) {
  Value v;
  v.u = x;
  return newData(v, UintType);
}
Data newDataFloat(Float x) {
  Value v;
  v.f = x;
  return newData(v, FloatType);
}
Data newDataString(String x) {
  Value v;
  v.s = x;
  return newData(v, StringType);
}
Data newDataBool(Bool x) {
  Value v;
  v.b = x;
  return newData(v, BoolType);
}
Data newDataObject(Object x) {
  Value v;
  v.o = x;
  return newData(v, ObjectType);
}
Data newDataArray(Array x) {
  Value v;
  v.a = x;
  return newData(v, ArrayType);
}
Data newDataNull() {
  Value v;
  return newData(v, NullType);
}

void updateDataInt(Data d, Int x) { d->val.i = x; }
void updateDataUint(Data d, Uint x) { d->val.u = x; }
void updateDataFloat(Data d, Float x) { d->val.f = x; }
void updateDataString(Data d, String x) { d->val.s = x; }
void updateDataBool(Data d, Bool x) { d->val.b = x; }
void updateDataObject(Data d, Object x) { d->val.o = x; }
void updateDataArray(Data d, Array x) { d->val.a = x; }

Data updateData(Data d, Value newData) {
  d->val = newData;
  return d;
}
Data updateType(Data d, DataType type) {
  d->type = type;
  return d;
}
void freeData(Data data) {
  DataType t = data->type;
  if (t == StringType)
    freeString(data->val.s);
  if (t == ObjectType)
    freeObject(data->val.o);
  if (t == ArrayType)
    freeArray(data->val.a);
  free(data);
}

Data shallowCopy(Data original){
  Data copy=malloc(sizeof(struct vmData));
  memcpy(copy,original,sizeof(struct vmData));
  return copy;
}

#define deepCopyString(s) fromString(getStringData(s),getStringLength(s))

static void deepCopyObjectIterator(String key,Data value,void*arg1,void*arg2){
  Object o=arg1;
  String s=deepCopyString(key);
  Data d=deepCopy(value);
  putObject(o,s,d);
}
static void deepCopArrayIterator(Data data,void*arg1,void*arg2){
  Array a=arg1;
  Data d=deepCopy(data);
  putArray(a,d);
}

static void deepCopyArray(Data copy){
  Array a=newArray();
  iterateArray(copy->val.a,deepCopArrayIterator,a,NULL);
  copy->val.a=a;
}

static void deepCopyObject(Data copy){
  Object o=newObject();
  iterateObject(copy->val.o,deepCopyObjectIterator,o,NULL);
  copy->val.o=o;
}

Data deepCopy(Data original){
  Data copy=shallowCopy(original);
  switch(copy->type){
    case StringType:
      copy->val.s=deepCopyString(copy->val.s);
      break;
    case ObjectType:
      deepCopyObject(copy);
      break;
    case ArrayType:
      deepCopyArray(copy);
      break;
    default:
      break;
  }
  return copy;
}

void encodeWatson(VM vm, Data data) {
  dataMap[data->type].encodeWatson(vm, data->val);
}

json_t *encodeJson(Data data) { return dataMap[data->type].encodeJson(data); }

struct fy_node *encodeYaml(struct fy_document *doc, Data data) {
  return dataMap[data->type].encodeYaml(doc, data);
}

DataType getDataType(Data data) { return data->type; }
