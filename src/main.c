#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/libwatson.h"

struct destination {
    IOFormat format;
    enum {
        File, Buffer
    } destType;
    union {
        FILE *file;
        struct {
            char *buf;
            size_t len;
        } buffer;
    } dest;
};
struct args {
    struct destination input, output;
};

void printHelp(char *argv[]) {
    printf("usage: %s --from TYPE --to TYPE -src SOURCE --dest DESTINATION", argv[0]);
    puts("--from -f [watson|json|yaml] indicate the source format");
    puts("--to   -t [watson|json|yaml] indicate the destination format");
    puts("--src  -s [file|string]      indicate the source");
    puts("--dest -d file               indicate the destination (will be overwritten)");
    puts("--help -h                    show this help message");
    puts("By default the values are --from json --to watson -src stdin --dest stdout");
    puts("All parameter are optional");
    puts("The src and dest string are null terminated, so \\0 can't be used");
}

IOFormat stringToFormat(char*str){
    if(strcmp(str,"watson")==0)return Watson;
    if(strcmp(str,"json")==0)return Json;
    if(strcmp(str,"yaml")==0)return Yaml;
    fputs("Invalid format, use [watson|json|yaml]",stderr);
    exit(1);
}

void applyDestination(char*str,struct destination *dest,int isOutput){
    FILE*f=fopen(str,isOutput?"w":"r");
    if(f){
        dest->destType=File;
        dest->dest.file=f;
    }else if(!isOutput){
        dest->destType=Buffer;
        dest->dest.buffer.buf=str;
        dest->dest.buffer.len=strlen(str);
    }else{
        fputs("Unable to open the destination file\n",stderr);
        exit(1);
    }
}

void parseArgument(struct args *args, int argc, char *argv[]) {
    int i;
    args->input.dest.file = stdin;
    args->input.format = Json;
    args->input.destType = File;

    args->output.dest.file = stdout;
    args->output.format = Watson;
    args->output.destType = File;

    if (argc == 1 || strcmp("--help", argv[1]) == 0 ||strcmp("--h", argv[1]) == 0) {
        printHelp(argv);
        exit(0);
    }

    for(i=1;i<argc-1;i++){
        if(argv[i][0]!='-')continue;
        if(strcmp("--from", argv[i]) == 0 ||strcmp("-f", argv[i]) == 0){
            args->input.format=stringToFormat(argv[++i]);
        }
        if(strcmp("--to",   argv[i]) == 0 ||strcmp("-t", argv[i]) == 0){
            args->output.format=stringToFormat(argv[++i]);
        }
        if(strcmp("--src",  argv[i]) == 0 ||strcmp("-s", argv[i]) == 0){
            applyDestination(argv[++i],&args->input,0);
        }
        if(strcmp("--dest", argv[i]) == 0 ||strcmp("-d", argv[i]) == 0){
            applyDestination(argv[++i],&args->input,1);
        }
    }
}

int main(int argc, char *argv[]) {
    struct args a;
    parseArgument(&a,argc,argv);
    if(a.input.format==File){
        watson_write_from_file_to_file(a.input.format,a.output.format,a.input.dest.file,a.output.dest.file);
    }else{
        watson_write_from_buffer_to_file(a.input.format,a.output.format,a.input.dest.buffer.buf,a.input.dest.buffer.len,a.output.dest.file);
    }

    return 0;
}
/*
❯ valgrind --leak-check=full ./watsonC
==39341== Memcheck, a memory error detector
==39341== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==39341== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==39341== Command: ./watsonC
==39341==
00==39341==
==39341== HEAP SUMMARY:
==39341==     in use at exit: 158,961,812 bytes in 2,627,313 blocks
==39341==   total heap usage: 5,548,994 allocs, 2,921,681 frees, 212,901,086 bytes allocated
==39341==
==39341== 7 bytes in 1 blocks are possibly lost in loss record 1 of 47
==39341==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==39341==    by 0x167BFC: fromString (string.c:18)
==39341==    by 0x110253: parseJson (decode.c:35)
==39341==    by 0x1100A7: parseArray (decode.c:10)
==39341==    by 0x110220: parseJson (decode.c:33)
==39341==    by 0x1100A7: parseArray (decode.c:10)
==39341==    by 0x110220: parseJson (decode.c:33)
==39341==    by 0x1102D2: jsonExecute (decode.c:52)
==39341==    by 0x110372: parseJsonFromStream (decode.c:60)
==39341==    by 0x10BF5D: watson_write_from_file_to_file (libwatson.c:28)
==39341==    by 0x10B8E3: main (main.c:77)
==39341==
==39341== 16 bytes in 1 blocks are possibly lost in loss record 2 of 47
==39341==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==39341==    by 0x160CA2: newData (data.c:35)
==39341==    by 0x160D6E: newDataString (data.c:59)
==39341==    by 0x11025B: parseJson (decode.c:35)
==39341==    by 0x1100A7: parseArray (decode.c:10)
==39341==    by 0x110220: parseJson (decode.c:33)
==39341==    by 0x1100A7: parseArray (decode.c:10)
==39341==    by 0x110220: parseJson (decode.c:33)
==39341==    by 0x1102D2: jsonExecute (decode.c:52)
==39341==    by 0x110372: parseJsonFromStream (decode.c:60)
==39341==    by 0x10BF5D: watson_write_from_file_to_file (libwatson.c:28)
==39341==    by 0x10B8E3: main (main.c:77)
==39341==
==39341== 24 bytes in 1 blocks are possibly lost in loss record 5 of 47
==39341==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==39341==    by 0x16752D: newArray (array.c:14)
==39341==    by 0x11008D: parseArray (decode.c:6)
==39341==    by 0x110220: parseJson (decode.c:33)
==39341==    by 0x1100A7: parseArray (decode.c:10)
==39341==    by 0x110220: parseJson (decode.c:33)
==39341==    by 0x1102D2: jsonExecute (decode.c:52)
==39341==    by 0x110372: parseJsonFromStream (decode.c:60)
==39341==    by 0x10BF5D: watson_write_from_file_to_file (libwatson.c:28)
==39341==    by 0x10B8E3: main (main.c:77)
==39341==
==39341== 24 bytes in 1 blocks are possibly lost in loss record 6 of 47
==39341==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==39341==    by 0x167BEC: fromString (string.c:17)
==39341==    by 0x110253: parseJson (decode.c:35)
==39341==    by 0x1100A7: parseArray (decode.c:10)
==39341==    by 0x110220: parseJson (decode.c:33)
==39341==    by 0x1100A7: parseArray (decode.c:10)
==39341==    by 0x110220: parseJson (decode.c:33)
==39341==    by 0x1102D2: jsonExecute (decode.c:52)
==39341==    by 0x110372: parseJsonFromStream (decode.c:60)
==39341==    by 0x10BF5D: watson_write_from_file_to_file (libwatson.c:28)
==39341==    by 0x10B8E3: main (main.c:77)
==39341==
==39341== 48 bytes in 3 blocks are possibly lost in loss record 9 of 47
==39341==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==39341==    by 0x160CA2: newData (data.c:35)
==39341==    by 0x160CEA: newDataInt (data.c:44)
==39341==    by 0x110271: parseJson (decode.c:37)
==39341==    by 0x1100A7: parseArray (decode.c:10)
==39341==    by 0x110220: parseJson (decode.c:33)
==39341==    by 0x1100A7: parseArray (decode.c:10)
==39341==    by 0x110220: parseJson (decode.c:33)
==39341==    by 0x1102D2: jsonExecute (decode.c:52)
==39341==    by 0x110372: parseJsonFromStream (decode.c:60)
==39341==    by 0x10BF5D: watson_write_from_file_to_file (libwatson.c:28)
==39341==    by 0x10B8E3: main (main.c:77)
==39341==
==39341== 56 (40 direct, 16 indirect) bytes in 1 blocks are definitely lost in loss record 10 of 47
==39341==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==39341==    by 0x160503: newVM (watsonVM.c:26)
==39341==    by 0x16059F: newFileVM (watsonVM.c:42)
==39341==    by 0x111751: writeWatsonDataToStream (encode.c:45)
==39341==    by 0x10BF86: watson_write_from_file_to_file (libwatson.c:29)
==39341==    by 0x10B8E3: main (main.c:77)
==39341==
==39341== 56 (40 direct, 16 indirect) bytes in 1 blocks are definitely lost in loss record 11 of 47
==39341==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==39341==    by 0x160503: newVM (watsonVM.c:26)
==39341==    by 0x16059F: newFileVM (watsonVM.c:42)
==39341==    by 0x110FFF: parseWatsonFromStream (decode.c:4)
==39341==    by 0x10BF5D: watson_write_from_file_to_file (libwatson.c:28)
==39341==    by 0x10B95C: main (main.c:81)
==39341==
==39341== 64 bytes in 4 blocks are possibly lost in loss record 12 of 47
==39341==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==39341==    by 0x167578: putArray (array.c:22)
==39341==    by 0x1100B9: parseArray (decode.c:10)
==39341==    by 0x110220: parseJson (decode.c:33)
==39341==    by 0x1100A7: parseArray (decode.c:10)
==39341==    by 0x110220: parseJson (decode.c:33)
==39341==    by 0x1102D2: jsonExecute (decode.c:52)
==39341==    by 0x110372: parseJsonFromStream (decode.c:60)
==39341==    by 0x10BF5D: watson_write_from_file_to_file (libwatson.c:28)
==39341==    by 0x10B8E3: main (main.c:77)
==39341==
==39341== 12,516,594 (16 direct, 12,516,578 indirect) bytes in 1 blocks are definitely lost in loss record 41 of 47
==39341==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==39341==    by 0x160CA2: newData (data.c:35)
==39341==    by 0x160DEF: newDataArray (data.c:74)
==39341==    by 0x110228: parseJson (decode.c:33)
==39341==    by 0x1102D2: jsonExecute (decode.c:52)
==39341==    by 0x110372: parseJsonFromStream (decode.c:60)
==39341==    by 0x10BF5D: watson_write_from_file_to_file (libwatson.c:28)
==39341==    by 0x10B8E3: main (main.c:77)
==39341==
==39341== 12,685,902 (16 direct, 12,685,886 indirect) bytes in 1 blocks are definitely lost in loss record 42 of 47
==39341==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==39341==    by 0x160CA2: newData (data.c:35)
==39341==    by 0x160DEF: newDataArray (data.c:74)
==39341==    by 0x16B796: vmAnew (commands.c:76)
==39341==    by 0x16063E: parseCommandLexar (watsonVM.c:53)
==39341==    by 0x160673: parseCommand (watsonVM.c:58)
==39341==    by 0x111019: parseWatsonFromStream (decode.c:6)
==39341==    by 0x10BF5D: watson_write_from_file_to_file (libwatson.c:28)
==39341==    by 0x10B95C: main (main.c:81)
==39341==
==39341== 133,758,077 (152 direct, 133,757,925 indirect) bytes in 1 blocks are definitely lost in loss record 47 of 47
==39341==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==39341==    by 0x11A711: fy_document_create (fy-doc.c:2962)
==39341==    by 0x10FB75: writeYamlDataToStream (encode.c:63)
==39341==    by 0x10BF86: watson_write_from_file_to_file (libwatson.c:29)
==39341==    by 0x10B95C: main (main.c:81)
==39341==
==39341== LEAK SUMMARY:
==39341==    definitely lost: 264 bytes in 5 blocks
==39341==    indirectly lost: 158,960,421 bytes in 2,627,295 blocks
==39341==      possibly lost: 183 bytes in 11 blocks
==39341==    still reachable: 944 bytes in 2 blocks
==39341==         suppressed: 0 bytes in 0 blocks
==39341== Reachable blocks (those to which a pointer was found) are not shown.
==39341== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==39341==
==39341== For lists of detected and suppressed errors, rerun with: -s
==39341== ERROR SUMMARY: 11 errors from 11 contexts (suppressed: 0 from 0)

 * */