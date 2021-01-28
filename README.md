# watson-c

A C implementation of [WATSON](https://github.com/genkami/watson)

## Prerequisites

This version of the app needs [gcc](https://gcc.gnu.org/), [pkg-config](https://www.freedesktop.org/wiki/Software/pkg-config/), [libfyaml v0.5.7](https://github.com/pantoniou/libfyaml) and [Jansson v2.14](https://github.com/akheron/jansson) to be installed

## Building

Build the watson-c executable with the below command.

```sh
make build
```

## Usage

The following command convert from WATSON to `JSON/Yaml`, if neither a file nor a string is passed, stdin will be used

```sh
./watson-c decode -t [json|yaml] <file|string>
```

The following command convert from `JSON/Yaml` to WATSON , if neither a file nor a string is passed, stdin will be used

```sh
./watson-c encode -t [json|yaml] <file|string>
```
