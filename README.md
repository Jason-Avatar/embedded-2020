# Embedded Systems @ NCKU EE

Code and docs

## Development

### Setup

Install clang-format and hooks

```
sudo apt install clang-format
make hooks
```

### Coding style

Coding style is enforced by [clang-format](https://clang.llvm.org/docs/ClangFormat.html). It is called in a pre-commit hook.

The files should be in UTF-8 encoding.

### Directory structure and file names

Put your C code in `src/`.
Each entry point should have filename in form `ID-short-name.c`, e.g. `06-led-matrix.c`. 

File names should not contain whitespaces. Seperate words with hyphens (`-`) instead.

## Instructions

### Building

Requirements:
* libmraa
* GNU Make
* GCC


```
# build everything
make all
# build selected file
make bin/06
```


### Running

Binaries should run with sudo, e.g.
```
sudo bin/06
```