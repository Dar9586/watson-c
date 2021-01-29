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

IOFormat stringToFormat(char *str) {
    if (strcmp(str, "watson") == 0)return Watson;
    if (strcmp(str, "json") == 0)return Json;
    if (strcmp(str, "yaml") == 0)return Yaml;
    fputs("Invalid format, use [watson|json|yaml]", stderr);
    exit(1);
}

void applyDestination(char *str, struct destination *dest, int isOutput) {
    FILE *f = fopen(str, isOutput ? "w" : "r");
    if (f) {
        dest->destType = File;
        dest->dest.file = f;
    } else if (!isOutput) {
        dest->destType = Buffer;
        dest->dest.buffer.buf = str;
        dest->dest.buffer.len = strlen(str);
    } else {
        fputs("Unable to open the destination file\n", stderr);
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

    if (argc == 1 || strcmp("--help", argv[1]) == 0 || strcmp("--h", argv[1]) == 0) {
        printHelp(argv);
        exit(0);
    }

    for (i = 1; i < argc - 1; i++) {
        if (argv[i][0] != '-')continue;
        if (strcmp("--from", argv[i]) == 0 || strcmp("-f", argv[i]) == 0) {
            args->input.format = stringToFormat(argv[++i]);
        }
        if (strcmp("--to", argv[i]) == 0 || strcmp("-t", argv[i]) == 0) {
            args->output.format = stringToFormat(argv[++i]);
        }
        if (strcmp("--src", argv[i]) == 0 || strcmp("-s", argv[i]) == 0) {
            applyDestination(argv[++i], &args->input, 0);
        }
        if (strcmp("--dest", argv[i]) == 0 || strcmp("-d", argv[i]) == 0) {
            applyDestination(argv[++i], &args->input, 1);
        }
    }
}

int main(int argc, char *argv[]) {
    struct args a;
    parseArgument(&a, argc, argv);
    if (a.input.format == File) {
        watson_write_from_file_to_file(a.input.format, a.output.format, a.input.dest.file, a.output.dest.file);
    } else {
        watson_write_from_buffer_to_file(a.input.format, a.output.format, a.input.dest.buffer.buf,
                                         a.input.dest.buffer.len, a.output.dest.file);
    }

    return 0;
}
