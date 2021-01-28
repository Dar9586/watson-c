AUTOMAKE_OPTIONS = subdir-objects
include_HEADERS = src/libs.h
bin_PROGRAMS = watson-c
watson_c_SOURCES = src/watson/decode.c src/watson/encode.c src/json/encode.c src/yaml/encode.c src/yaml/decode.c src/json/decode.c src/data/array.c src/vm/commands.c src/vm/data.c src/data/object.c src/vm/stack.c src/data/string.c src/vm/watsonVM.c src/main.c 
watson_c_CFLAGS = `pkg-config --cflags jansson libfyaml`
watson_c_LDFLAGS = `pkg-config --libs jansson libfyaml`
watson_c_LDADD = -ljansson -lfyaml-0.5
