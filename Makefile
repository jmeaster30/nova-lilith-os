XCC=./cross-compiler/bin/i686-elf-g++
XASM=./cross-compiler/bin/i686-elf-as

CFLAGS=-ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti
LDFLAGS=-ffreestanding -O2 -nostdlib

SOURCES= \
src/kernel/kernel.cpp \
src/kernel/terminal/terminal.cpp \
src/kernel/libk/abort.cpp \
src/kernel/libk/io.cpp \

INCLUDE= \
src/kernel \

OBJECTS=$(SOURCES:.cpp=.o)
LINK_OBJS=$(addprefix build/,$(OBJECTS))

$(info linkobjects is $(LINK_OBJS))

build/boot.o : src/boot.s
	${XASM} src/boot.s -o build/boot.o

.cpp.o : 
	mkdir -p build/$(@D) $(INCLUDE)
	$(XCC) -c $(CFLAGS) $(INCLUDE:%=-I %) $< -o build/$@

nova-lilith-os.bin : build build/boot.o ${OBJECTS} src/linker.ld
	${XCC} -T src/linker.ld -o build/nova-lilith-os.bin ${LDFLAGS} build/boot.o ${LINK_OBJS} -lgcc

build :
	mkdir build

.PHONY: clean and-run

and-run : nova-lilith-os.bin
	qemu-system-i386 -kernel build/nova-lilith-os.bin

clean :
	rm -rf build
