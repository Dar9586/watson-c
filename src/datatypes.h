static const long long nanVal = 0x7FF0000000000001LL;
static const long long infVal = 0x7FF0000000000000LL;
#define itof(f) (*((double *)&(f)))
#define INF itof(infVal)
#define NAN itof(nanVal)

typedef int64_t Int;
typedef uint64_t Uint;
typedef double Float;
typedef struct string *String;
typedef uint8_t Bool;
typedef struct object *Object;
typedef struct array *Array;

typedef union {
  Int i;
  Uint u;
  Float f;
  String s;
  Bool b;
  Object o;
  Array a;
} Value;

typedef enum { LexerA, LexerS } Lexer;
typedef enum { Encode, Decode } ParseMethod;
typedef enum { Watson, Json, Yaml } IOFormat;


typedef struct stack *Stack;
typedef struct vmData *Data;
typedef struct vm *VM;

struct vm {
  Stack stack;
  Lexer lexer;
};


typedef enum {
  Inew,Iinc,Ishl,Iadd,Ineg,Isht,Itof,Itou,
  Finf,Fnan,Fneg,
  Snew,Sadd,
  Onew,Oadd,
  Anew,Aadd,
  Bnew,Bneg,
  Nnew,
  Gdup,Gpop,Gswp
} CommandCode;

typedef enum {
  IntType,
  UintType,
  FloatType,
  StringType,
  NullType,
  BoolType,
  ObjectType,
  ArrayType
} DataType;


#define MAX_LONG_SIZE 20
#define LEXER_COUNT 2
#define PARSE_METHOD_COUNT 2
#define COMMAND_COUNT 23
#define IO_FORMAT_COUNT 3
#define VAR_TYPE_COUNT 8
#define FLOAT_PRECISION_JSON 3
#define VM_TRUE 1
#define VM_FALSE 0
