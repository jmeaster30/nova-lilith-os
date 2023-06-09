#!/bin/bash

sd = ${PWD##*/}
case sd in
    "cross-compiler")
        echo "Already in cross-compiler directory"
        ;;
    "nova-lilith-os")
        echo "Not in cross-compiler directory"
        cd cross-compiler
        ;;
esac

#build cross-compiler
export PREFIX="$(pwd)"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"

mkdir bin

mkdir build-binutils
cd build-binutils
../binutils-gdb/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make
make install
cd ..

which -- $TARGET-as || echo $TARGET-as is not in the PATH
 
mkdir build-gcc
cd build-gcc
../gcc/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
make all-gcc
make all-target-libgcc
make install-gcc
make install-target-libgcc
cd ..
case sd in
    "cross-compiler")
        echo "Started in cross-compiler directory"
        ;;
    "nova-lilith-os")
        cd ..
        ;;
esac
