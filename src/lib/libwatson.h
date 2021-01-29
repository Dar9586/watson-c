#ifndef WATSONC_LIBWATSON_H
#define WATSONC_LIBWATSON_H

typedef enum {
    Watson, Json, Yaml
} IOFormat;

/*
 * Those functions return -1 on error and 0 on success
 * */
int watson_write_from_buffer_to_buffer(IOFormat input, IOFormat output, char *source, size_t source_size, char *dest,
                                       size_t dest_size);

int watson_write_from_buffer_to_file(IOFormat input, IOFormat output, char *source, size_t source_size, FILE *dest);

int watson_write_from_file_to_buffer(IOFormat input, IOFormat output, FILE *source, char *dest, size_t dest_size);

int watson_write_from_file_to_file(IOFormat input, IOFormat output, FILE *source, FILE *dest);

#endif //WATSONC_LIBWATSON_H
