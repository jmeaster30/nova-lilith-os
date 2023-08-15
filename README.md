# nova-lilith-os

I want to learn about operating systems so this is my toy operating system. I am following instructions from the [osdev wiki](https://wiki.osdev.org/). I am not super interested in following a particular standard but I do want to try to implement an exokernel. If I fail at the exokernel I'll just switch to a microkernel type architecture.

## Goals

- Learn about how to develop a kernel
- Learn about operating systems
- Develop an exokernal maybe
- Develop a functional operating system that I can run and use for programming on one of my computers

## How to build

First, install some dependencies for your system
> `sudo apt install build-essential bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo`

Build the cross-compiler
> `make cross-compiler`

Build and run the OS
> `make and-run`

## How to debug

Build and run the OS + GDB with debug options
> `make and-debug`

You will get QEMU set up with a connection open to GDB and GDB will start, attach itself to that QEMU connection.
QEMU starts paused waiting for GDB to start it so you can set your breakpoints and type continue in the host console to make the OS run.

## Cross compiler

This is set up from this guide [GCC Cross-Compiler](https://wiki.osdev.org/GCC_Cross-Compiler) on the osdev wiki.
