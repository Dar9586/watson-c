#include "libs.h"

const struct {
    Data (*parseStream)(FILE *);

    Data (*parseString)(const char *, size_t);

    int (*writeToStream)(Data data, FILE *fp);

    int (*writeToBuffer)(Data data, char *buf, size_t len);

} decodeMap[IO_FORMAT_COUNT] = {
        {parseWatsonFromStream, parseWatsonFromString, writeWatsonDataToStream, writeWatsonDataToBuffer},
        {parseJsonFromStream,   parseJsonFromString,   writeJsonDataToStream,   writeJsonDataToBuffer},
        {parseYamlFromStream,   parseYamlFromString,   writeYamlDataToStream,   writeYamlDataToBuffer}
};

int watson_write_from_buffer_to_buffer(IOFormat input, IOFormat output, char *source, size_t source_size, char *dest,
                                       size_t dest_size) {
    if (source == NULL || dest == NULL)return -1;
    Data d = decodeMap[input].parseString(source, source_size);
    if (d == NULL)return -2;
    int k = decodeMap[output].writeToBuffer(d, dest, dest_size);
    deepFreeData(d);
    return k;
}

int watson_write_from_buffer_to_file(IOFormat input, IOFormat output, char *source, size_t source_size, FILE *dest) {
    if (source == NULL || dest == NULL)return -1;
    Data d = decodeMap[input].parseString(source, source_size);
    if (d == NULL)return -2;
    int k = decodeMap[output].writeToStream(d, dest);
    deepFreeData(d);
    return k;
}

int watson_write_from_file_to_buffer(IOFormat input, IOFormat output, FILE *source, char *dest, size_t dest_size) {
    if (source == NULL || dest == NULL)return -1;
    Data d = decodeMap[input].parseStream(source);
    if (d == NULL)return -2;
    int k = decodeMap[output].writeToBuffer(d, dest, dest_size);
    deepFreeData(d);
    return k;
}

int watson_write_from_file_to_file(IOFormat input, IOFormat output, FILE *source, FILE *dest) {
    if (source == NULL || dest == NULL)return -1;
    Data d = decodeMap[input].parseStream(source);
    if (d == NULL)return -2;
    int k = decodeMap[output].writeToStream(d, dest);
    deepFreeData(d);
    return k;
}


