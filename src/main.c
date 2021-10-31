#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <getopt.h>

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

void init_args(struct args *args);
IOFormat stringToFormat(char *str);
void applyInput(char *str, struct destination *dest);
void applyOutput(char *str, struct destination *dest);
void applyDestination(char *str, struct destination *dest, int isOutput);
void printHelp(char *argv[]);
void parse_args(struct args *args, int argc, char **argv);
void init_args(struct args *args);

static const struct option longopts[] = {
        {.name = "from", .has_arg = required_argument, .val = 'f'},   /*Install webcam driver or pulseaudio*/
        {.name = "to", .has_arg = required_argument, .val = 't'}, /*Uninstall webcam driver or pulseaudio*/
        {.name = "src", .has_arg = required_argument, .val = 's'},
        {.name = "dest", .has_arg = required_argument, .val = 'd'},
        {.name = "help", .has_arg = no_argument, .val = 'h'},
        {},
};

IOFormat stringToFormat(char *str) {
    if (strcmp(str, "watson") == 0)return Watson;
    if (strcmp(str, "json") == 0)return Json;
    if (strcmp(str, "yaml") == 0)return Yaml;
    fputs("Invalid format, use [watson|json|yaml]", stderr);
    exit(1);
}

void applyInput(char *str, struct destination *dest) {
    FILE *f = fopen(str, "r");
    if (f) {
        dest->destType = File;
        dest->dest.file = f;
    } else {
        dest->destType = Buffer;
        dest->dest.buffer.buf = str;
        dest->dest.buffer.len = strlen(str);
    }
}

void applyOutput(char *str, struct destination *dest) {
    FILE *f = fopen(str, "w");
    if (f == NULL) {
        fputs("Unable to open the destination file\n", stderr);
        exit(1);
    }
    dest->destType = File;
    dest->dest.file = f;
}

void applyDestination(char *str, struct destination *dest, int isOutput) {
    if (strcmp("-", str) == 0) { //stdin/stdout is already default
        return;
    }
    if (isOutput)applyOutput(str, dest);
    else applyInput(str, dest);
}

void printHelp(char *argv[]) {
    printf("usage: %s --from TYPE --to TYPE -src SOURCE --dest DESTINATION\n", argv[0]);
    puts("--from    [watson|json|yaml] indicate the source format                      (default json)");
    puts("--to      [watson|json|yaml] indicate the destination format                 (default watson)");
    puts("--src     [file|string]      indicate the source                             (default stdin)");
    puts("--dest    file               indicate the destination (will be overwritten)  (default stdout)");
    puts("--help -h                    show this help message");
    puts("By default the values are --from json --to watson -src stdin --dest stdout");
    puts("All parameter are optional");
}

void parse_args(struct args *args, int argc, char **argv) {

    int opt;

    init_args(args);

    for (;;) {
        opt = getopt_long(argc, argv, "h", longopts, NULL);
        if (opt == -1)
            return;
        switch (opt) {
            case 'f':
                args->input.format = stringToFormat(optarg);
                break;
            case 't':
                args->output.format = stringToFormat(optarg);
                break;
            case 's':
                applyDestination(optarg, &args->input, false);
                break;
            case 'd':
                applyDestination(optarg, &args->output, true);
                break;
            case 'h':
                printHelp(argv);
                exit(0);
            default:
                exit(1);
        }
    }
}

void init_args(struct args *args) {
    args->input.dest.file = stdin;
    args->input.format = Json;
    args->input.destType = File;

    args->output.dest.file = stdout;
    args->output.format = Watson;
    args->output.destType = File;
}

int main(int argc, char *argv[]) {
    struct args a;
    parse_args(&a, argc, argv);
    if (a.input.destType == File) {
        watson_write_from_file_to_file(a.input.format, a.output.format, a.input.dest.file, a.output.dest.file);
    } else {
        watson_write_from_buffer_to_file(a.input.format, a.output.format, a.input.dest.buffer.buf,
                                         a.input.dest.buffer.len, a.output.dest.file);
    }

    return 0;
}
