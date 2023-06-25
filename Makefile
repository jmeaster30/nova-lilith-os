XCC=./cross-compiler/bin/i686-elf-g++
XASM=./cross-compiler/bin/i686-elf-as

CFLAGS=-ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -g
LDFLAGS=-ffreestanding -O2 -nostdlib
QEMUFLAGS= \
-display gtk \
-monitor stdio \

SOURCES= \
src/kernel/kernel.cpp \
src/kernel/terminal/terminal.cpp \
src/kernel/libk/abort.cpp \
src/kernel/libk/io.cpp \
src/kernel/libk/ringbuffer.cpp \
src/kernel/structures/descriptortable.cpp \
src/kernel/interrupts/interrupttable.cpp \
src/kernel/interrupts/interrupthandler.cpp \
src/kernel/interrupts/interruptwrapper.s \
src/kernel/interrupts/pic.cpp \
src/kernel/keyboard/keyboard.cpp \
src/kernel/memory/pagetableentry.cpp \
src/kernel/memory/pagedirectoryentry.cpp \

INCLUDE= \
src/kernel \

CPP_OBJECTS=$(SOURCES:.cpp=.o)
OBJECTS=$(CPP_OBJECTS:.s=.o)
CRTBEGIN_OBJ:=$(shell $(XCC) $(CFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ:=$(shell $(XCC) $(CFLAGS) -print-file-name=crtend.o)
CRTI_OBJ=build/crti.o
CRTN_OBJ=build/crtn.o
LINK_OBJS=$(CRTI_OBJ) $(CRTBEGIN_OBJ) $(addprefix build/,$(OBJECTS)) $(CRTEND_OBJ) $(CRTN_OBJ)

$(info $$SOURCES is [${SOURCES}])
$(info $$LINK_OBJS is [${LINK_OBJS}])

build/boot.o : src/boot.s
	${XASM} src/boot.s -o build/boot.o

build/crti.o : src/kernel/crti.s
	${XASM} src/kernel/crti.s -o build/crti.o

build/crtn.o : src/kernel/crtn.s
	${XASM} src/kernel/crtn.s -o build/crtn.o

.cpp.o :
	mkdir -p build/$(@D)
	$(XCC) -c $< -o build/$@ $(CFLAGS) $(INCLUDE:%=-I%)

.s.o :
	mkdir -p build/$(@D)
	$(XASM) $^ -o build/$@

nova-lilith-os.bin : build build/boot.o build/crti.o build/crtn.o ${OBJECTS} src/linker.ld
	${XCC} -T src/linker.ld -o build/nova-lilith-os.bin ${LDFLAGS} build/boot.o ${LINK_OBJS} -lgcc

build :
	mkdir build

.PHONY: clean and-debug and-run cross-compiler

and-run : nova-lilith-os.bin
	qemu-system-i386 ${QEMUFLAGS} -kernel build/nova-lilith-os.bin

and-debug : nova-lilith-os.bin
	qemu-system-i386 ${QEMUFLAGS} -s -S -kernel build/nova-lilith-os.bin &
	gdb vmlinux -ex 'target remote localhost:1234' -ex 'symbol-file build/nova-lilith-os.bin'

cross-compiler :
	git submodule init
	git submodule update
	./cross-compiler/build.sh

clean :
	rm -rf build
