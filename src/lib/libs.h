#ifndef WATSON_LIBS
#define WATSON_LIBS
/*to disable the inline of libfyaml and jansson*/
#define inline

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include<stdbool.h>
#include<regex.h>
#include "libwatson.h"
#include"../external/jansson/jansson.h"
#include"../external/libfyaml/libfyaml.h"
#include"datatypes.h"
#include"data/array.h"
#include"data/object.h"
#include"data/string.h"
#include"vm/stack.h"
#include"vm/watsonVM.h"
#include"vm/data.h"
#include"vm/commands.h"
#include"json/decode.h"
#include"yaml/decode.h"
#include"json/encode.h"
#include"yaml/encode.h"
#include"watson/encode.h"
#include"watson/decode.h"

#endif //WATSON_LIBS
