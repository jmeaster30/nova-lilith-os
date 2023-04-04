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

#### Prerequisites

The cross compiler is built from gcc and has some prerequisites before it can be built. If you are on a Debian-based linux then run the following command to get the proper prerequisites.

> `sudo apt install build-essential bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo`

See the [GCC Cross-Compiler](https://wiki.osdev.org/GCC_Cross-Compiler) on the osdev wiki for more info.

#### Makefile

The cross compiler can be built with the makefile so you can just run the following command.

> `make cross-compiler`

This command updates the submodules and calls the ./cross-compiler/build.sh script in one command.

#### Bash Script

The cross compiler can be built with the build.sh file in the cross-compiler folder but you need to make sure you pull the submodules if you haven't already.

> `git submodule init`
> `git submodule update`

Once those are updated run the following commands.

> `cd cross-compiler`
> `./build.sh`

### Build and run the os in QEMU

You must build the cross-compiler first. After that, just run the following command.

> `make and-run`
