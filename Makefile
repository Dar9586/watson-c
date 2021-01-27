CC=gcc
CWD=.
OUT=$(CWD)/out
SRC=$(CWD)/src
LIB_FOLDER=$(CWD)/libs
FLAGS= -g -Wall --ansi
LIBS=`pkg-config --cflags --libs jansson` `pkg-config --cflags --libs libfyaml`

clean:
	rm -rf $(OUT)
	mkdir $(OUT)
build: clean
	$(CC) $(SRC)/watson/decode.c $(FLAGS) $(LIBS) -c -o $(OUT)/decodeWatson.o
	$(CC) $(SRC)/watson/encode.c $(FLAGS) $(LIBS) -c -o $(OUT)/encodeWatson.o
	$(CC) $(SRC)/json/encode.c   $(FLAGS) $(LIBS) -c -o $(OUT)/encodeJson.o
	$(CC) $(SRC)/yaml/encode.c   $(FLAGS) $(LIBS) -c -o $(OUT)/encodeYaml.o
	$(CC) $(SRC)/yaml/decode.c   $(FLAGS) $(LIBS) -c -o $(OUT)/decodeYaml.o
	$(CC) $(SRC)/json/decode.c   $(FLAGS) $(LIBS) -c -o $(OUT)/decodeJson.o
	$(CC) $(SRC)/data/array.c    $(FLAGS) $(LIBS) -c -o $(OUT)/array.o
	$(CC) $(SRC)/vm/commands.c   $(FLAGS) $(LIBS) -c -o $(OUT)/commands.o
	$(CC) $(SRC)/vm/data.c       $(FLAGS) $(LIBS) -c -o $(OUT)/data.o
	$(CC) $(SRC)/data/object.c   $(FLAGS) $(LIBS) -c -o $(OUT)/object.o
	$(CC) $(SRC)/vm/stack.c      $(FLAGS) $(LIBS) -c -o $(OUT)/stack.o
	$(CC) $(SRC)/data/string.c   $(FLAGS) $(LIBS) -c -o $(OUT)/string.o
	$(CC) $(SRC)/vm/watsonVM.c   $(FLAGS) $(LIBS) -c -o $(OUT)/watsonVM.o
	$(CC) $(SRC)/main.c          $(FLAGS) $(LIBS)    -o $(OUT)/main $(OUT)/*