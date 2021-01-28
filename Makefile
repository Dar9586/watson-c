CC=gcc
CWD=.
OUT=$(CWD)/out
SRC=$(CWD)/src
LIB_FOLDER=$(CWD)/libs
FLAGS= -g -Wall --ansi -Wextra -pedantic -Wno-long-long -Wno-unused-parameter
LIBS=`pkg-config --cflags --libs jansson` `pkg-config --cflags --libs libfyaml`

clean:
	rm -f $(CWD)/watson-c
	rm -rf $(OUT)

$(OUT):
	mkdir $(OUT)
$(OUT)/decodeWatson.o:
	$(CC) $(SRC)/watson/decode.c $(FLAGS) $(LIBS) -c -o $(OUT)/decodeWatson.o
$(OUT)/encodeWatson.o:
	$(CC) $(SRC)/watson/encode.c $(FLAGS) $(LIBS) -c -o $(OUT)/encodeWatson.o
$(OUT)/encodeJson.o:
	$(CC) $(SRC)/json/encode.c   $(FLAGS) $(LIBS) -c -o $(OUT)/encodeJson.o
$(OUT)/encodeYaml.o:
	$(CC) $(SRC)/yaml/encode.c   $(FLAGS) $(LIBS) -c -o $(OUT)/encodeYaml.o
$(OUT)/decodeYaml.o:
	$(CC) $(SRC)/yaml/decode.c   $(FLAGS) $(LIBS) -c -o $(OUT)/decodeYaml.o
$(OUT)/decodeJson.o:
	$(CC) $(SRC)/json/decode.c   $(FLAGS) $(LIBS) -c -o $(OUT)/decodeJson.o
$(OUT)/array.o:
	$(CC) $(SRC)/data/array.c    $(FLAGS) $(LIBS) -c -o $(OUT)/array.o
$(OUT)/commands.o:
	$(CC) $(SRC)/vm/commands.c   $(FLAGS) $(LIBS) -c -o $(OUT)/commands.o
$(OUT)/data.o:
	$(CC) $(SRC)/vm/data.c       $(FLAGS) $(LIBS) -c -o $(OUT)/data.o
$(OUT)/object.o:
	$(CC) $(SRC)/data/object.c   $(FLAGS) $(LIBS) -c -o $(OUT)/object.o
$(OUT)/stack.o:
	$(CC) $(SRC)/vm/stack.c      $(FLAGS) $(LIBS) -c -o $(OUT)/stack.o
$(OUT)/string.o:
	$(CC) $(SRC)/data/string.c   $(FLAGS) $(LIBS) -c -o $(OUT)/string.o
$(OUT)/watsonVM.o:
	$(CC) $(SRC)/vm/watsonVM.c   $(FLAGS) $(LIBS) -c -o $(OUT)/watsonVM.o
$(CWD)/watson-c:
	$(CC) $(SRC)/main.c          $(FLAGS) $(LIBS)    -o watson-c $(OUT)/*

build: $(OUT) $(OUT)/decodeWatson.o $(OUT)/encodeWatson.o $(OUT)/encodeJson.o $(OUT)/encodeYaml.o $(OUT)/decodeYaml.o $(OUT)/decodeJson.o $(OUT)/array.o $(OUT)/commands.o $(OUT)/data.o $(OUT)/object.o $(OUT)/stack.o $(OUT)/string.o $(OUT)/watsonVM.o $(CWD)/watson-c

rebuild: clean build
