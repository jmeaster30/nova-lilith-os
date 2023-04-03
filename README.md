# nova-lilith-os

I want to learn about operating systems so this is my toy operating system. I am following instructions from the [osdev wiki](https://wiki.osdev.org/). I am not super interested in following a particular standard but I do want to try to implement an exokernel. If I fail at the exokernel I'll just switch to a microkernel type architecture.

## Goals

- Learn about how to develop a kernel
- Learn about operating systems
- Develop an exokernal maybe
- Develop a functional operating system that I can run and use for programming on one of my computers

### Notes

## How to build

### Build the cross-compiler

The cross-compiler can be built with the makefile so you can just run the following command.

> `make cross-compiler`

Or, it can be run with the build.sh file in the cross-compiler folder but you need to make sure you pull the submodules if you haven't already.

> `git submodule init`
> `git submodule update`

Once those are updated run the following commands.

> `cd cross-compiler`
> `./build.sh`

I want this to be baked into the make file so all you need to do is a single command to build the os.

### Build and run the os in QEMU

You must build the cross-compiler first. After that, just run the following command.

> `make and-run`
