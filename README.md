# watson-c

A C implementation of the esoteric configuration language [WATSON](https://github.com/genkami/watson)

## Prerequisites

This version of the app needs [cmake](https://cmake.org/)

## Building

Build the watson-c executable with the below command.

```sh
mkdir build
cd build
cmake ..
make
```

## Usage

```text
usage: ./watsonC --from TYPE --to TYPE -src SOURCE --dest DESTINATION

--from -f [watson|json|yaml] indicate the source format
--to   -t [watson|json|yaml] indicate the destination format
--src  -s [file|string]      indicate the source
--dest -d file               indicate the destination (will be overwritten)
```

## Libraries

This app uses the following libraries:

- [libfyaml v0.5.7](https://github.com/pantoniou/libfyaml)
- [Jansson v2.14](https://github.com/akheron/jansson)

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
