# watson-c

A C implementation of the esoteric configuration language [WATSON](https://github.com/genkami/watson)

## Prerequisites

This version of the app needs [gcc](https://gcc.gnu.org/), [pkg-config](https://www.freedesktop.org/wiki/Software/pkg-config/), [libfyaml v0.5.7](https://github.com/pantoniou/libfyaml) and [Jansson v2.14](https://github.com/akheron/jansson) to be installed

## Building

Build the watson-c executable with the below command.

```sh
autoreconf -vfi
./configure
make
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

## License

```text
   Copyright 2021 Dar9586

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
```
