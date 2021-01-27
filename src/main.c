#include "libs.h"

struct args {
  ParseMethod method;
  IOFormat input,output;
  int stackSize;
  Lexer lexer;
  FILE*inputFile;
  char*buf;
  size_t len;
};

const struct{
  Data (*parseStream)(FILE*);
  Data (*parseString)(const char*,size_t);
}decodeMap[IO_FORMAT_COUNT]={
  {parseWatsonFromStream,parseWatsonFromString},
  {parseJsonFromStream,parseJsonFromString},
  {parseYamlFromStream,parseYamlFromString}
};

void parseArgument(struct args *args, int argc, char *argv[]) {
  int i,block=0;
  FILE*f=NULL;
  IOFormat *target;
  args->lexer = LexerA;
  args->input = Json;
  args->output = Watson;
  args->stackSize = 1024;
  args->inputFile=stdin;
  args->buf=NULL;
  args->len=0;

  if (argc < 2 ||
      ((strcmp(argv[1], "encode") != 0) && (strcmp(argv[1], "decode") != 0))) {
    printf("usage: %s [decode|encode]\n", argv[0]);
    exit(0);
  }

  if(!strcmp(argv[1], "encode")){
    target=&args->input;
    args->method=Encode;
    args->output=Watson;
  }else{
    target=&args->output;
    args->method=Decode;
    args->input=Watson;
  }


  for (i = 2; i < argc; i++) {
    if (strcmp("-t", argv[i]) == 0) {
      i++;
      if(i==argc)exit(2);
      if (strcmp("json", argv[i]) == 0)
        *target = Json;
      else if (strcmp("yaml", argv[i]) == 0)
        *target = Yaml;
      else
        exit(1);
    }else if (strcmp("-", argv[i]) == 0){
      block=true;
      args->buf=NULL;
      args->inputFile=stdin;
    }else{
      if(block)continue;
      f=fopen(argv[i],"r");
      if(f==NULL)args->buf=argv[i];
      else args->inputFile=f;
    }
  }
  if(args->buf)args->len=strlen(args->buf);
}

int main(int argc, char *argv[]) {
  struct args arg;
  json_t*root;
  struct fy_document*doc=fy_document_create(NULL);
  parseArgument(&arg, argc, argv);
  Data d=arg.buf?decodeMap[arg.input].parseString(arg.buf,arg.len):decodeMap[arg.input].parseStream(arg.inputFile);
  switch(arg.output){
    case Watson:
      encodeWatson(newVM(LexerA),d);
      break;
    case Yaml:
      fy_document_set_root(doc,encodeYaml(doc,d));
      fy_emit_document_to_fp(doc,FYECF_SORT_KEYS,stdout);
      break;
    case Json:
      root=encodeJson(d);
      json_dumpf(root,stdout,JSON_REAL_PRECISION(FLOAT_PRECISION_JSON)|JSON_ENCODE_ANY|JSON_COMPACT|JSON_ENSURE_ASCII|JSON_SORT_KEYS|JSON_ESCAPE_SLASH);
      break;
  }
  return 0;
}
