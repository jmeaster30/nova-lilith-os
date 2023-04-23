XCC=./cross-compiler/bin/i686-elf-g++
XASM=./cross-compiler/bin/i686-elf-as

CFLAGS=-ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -g
LDFLAGS=-ffreestanding -O2 -nostdlib
QEMUFLAGS=

SOURCES= \
src/kernel/kernel.cpp \
src/kernel/terminal/terminal.cpp \
src/kernel/libk/abort.cpp \
src/kernel/libk/io.cpp \
src/kernel/structures/descriptortable.cpp \
src/kernel/interrupts/interrupttable.cpp \
src/kernel/interrupts/interrupthandler.cpp \
src/kernel/interrupts/interruptwrapper.s \
src/kernel/interrupts/pic.cpp \

INCLUDE= \
src/kernel \

CPP_OBJECTS=$(SOURCES:.cpp=.o)
OBJECTS=$(CPP_OBJECTS:.s=.o)
LINK_OBJS=$(addprefix build/,$(OBJECTS))

$(info $$SOURCES is [${SOURCES}])
$(info $$LINK_OBJS is [${LINK_OBJS}])

build/boot.o : src/boot.s
	${XASM} src/boot.s -o build/boot.o

.cpp.o :
	mkdir -p build/$(@D)
	$(XCC) -c $< -o build/$@ $(CFLAGS) $(INCLUDE:%=-I%)

.s.o :
	mkdir -p build/$(@D)
	$(XASM) $^ -o build/$@

nova-lilith-os.bin : build build/boot.o ${OBJECTS} src/linker.ld
	${XCC} -T src/linker.ld -o build/nova-lilith-os.bin ${LDFLAGS} build/boot.o ${LINK_OBJS} -lgcc

build :
	mkdir build

.PHONY: clean and-run cross-compiler

and-run : nova-lilith-os.bin
	qemu-system-i386 ${QEMUFLAGS} -kernel build/nova-lilith-os.bin

cross-compiler :
	git submodule init
	git submodule update
	./cross-compiler/build.sh

clean :
	rm -rf build
