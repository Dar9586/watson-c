#include "../libs.h"

void freeData(Data data);
Data updateType(Data d, DataType type);

Int valInt(Data data);
Uint valUint(Data data);
Float valFloat(Data data);
String valString(Data data);
Bool valBool(Data data);
Object valObject(Data data);
Array valArray(Data data);
Value val(Data data);

Data newDataInt(Int x);
Data newDataUint(Uint x);
Data newDataFloat(Float x);
Data newDataString(String x);
Data newDataBool(Bool x);
Data newDataObject(Object x);
Data newDataArray(Array x);
Data newDataNull();

void updateDataInt(Data d, Int x);
void updateDataUint(Data d, Uint x);
void updateDataFloat(Data d, Float x);
void updateDataString(Data d, String x);
void updateDataBool(Data d, Bool x);
void updateDataObject(Data d, Object x);
void updateDataArray(Data d, Array x);

void printData(Data data);

void encodeWatson(VM vm, Data data);

DataType getDataType(Data data);
void encodeWatson(VM vm, Data data);
Data deepCopy(Data data);
json_t *encodeJson(Data data);
struct fy_node *encodeYaml(struct fy_document *doc, Data data);