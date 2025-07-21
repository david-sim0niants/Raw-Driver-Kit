cmake_minimum_required(VERSION 3.13)
project(Raw-Driver-Kit ASM C)

set(CMAKE_C_STANDARD 11)

# Set compiler flags for kernel code
set(CMAKE_ASM_FLAGS "${DEFAULT_CMAKE_ASM_FLAGS} -x assembler-with-cpp")
set(COMMON_C_CXX_FLAGS "-no-pie -fno-pic -fno-ident -ffreestanding -fno-exceptions -nostdlib -nostdinc -fno-stack-protector -nostartfiles -lgcc")

set(CMAKE_C_FLAGS   "${DEFAULT_CMAKE_C_FLAGS} ${COMMON_C_CXX_FLAGS} -z noexecstack")
set(CMAKE_CXX_FLAGS "${DEFAULT_CMAKE_CXX_FLAGS} ${COMMON_C_CXX_FLAGS} -fno-rtti")

set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(CMAKE_STATIC_LIBRARY_SUFFIX ".elf")
set(CMAKE_EXECUTABLE_SUFFIX 	"")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

add_subdirectory(arch)
add_subdirectory(libc)
