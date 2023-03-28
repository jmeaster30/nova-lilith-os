# nova-lilith-os

I want to learn about operating systems so this is my toy operating system.

## Goals

- Learn about how to develop a kernel
- Learn about operating systems
- Develop a functional operating system that I can run and use for programming on one of my computers

### Notes

## How to build

### Build the cross-compiler

1. `cd cross-compiler`
1. `./build.sh`

I want this to be baked into the make file so all you need to do is a single command to build the os.

### Build and run the os in QEMU

You must build the cross-compiler first. After that, just run `make and-run` from the root of the repository.
