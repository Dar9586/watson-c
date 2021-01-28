# watson-c

A C implementation of [WATSON](https://github.com/genkami/watson)

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
