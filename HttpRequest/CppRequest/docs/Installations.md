### Install cppRequest

0. create a folder for c++ libraries
1. clone cppRequest repo <https://github.com/libcpr/cpr.git> into this folder
2. execute following commands in cpr repo folder
```bash
mkdir build && cd build
cmake .. -DCPR_USE_SYSTEM_CURL=ON
cmake --build .
cmake --install . --prefix build
```

### Build, Run, Debug

1. adjust your Makefile according to your cprRequest location
2. adjust .vscode files according to your cppRequest location
