cmake_minimum_required(VERSION 3.22)

set(TARGET "i686-elf")

set(CMAKE_C_COMPILER ${CMAKE_CURRENT_SOURCE_DIR}/cross-compiler/bin/${TARGET}-gcc)
set(CMAKE_CXX_COMPILER ${CMAKE_CURRENT_SOURCE_DIR}/cross-compiler/bin/${TARGET}-g++)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

project(nova-lilith-os)

add_subdirectory(src)