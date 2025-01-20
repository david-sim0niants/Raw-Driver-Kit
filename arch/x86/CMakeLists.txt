set(x86_INCLOUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(TARGET_NAME rdksh32)

add_executable(${TARGET_NAME}
    entry.S main32.c ps2_keyboard.c timer.c intr/handlers.c intr/idt.c intr/pic.c intr/stubs.S)

set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/rdksh32.linker.ld)
set(LINK_OTHER_OPTIONS	"--gc-sections,--build-id=none,--whole-archive")
set(LINK_OPTIONS "LINKER:,-T${LINKER_SCRIPT},${LINK_OTHER_OPTIONS}")

target_link_options(${TARGET_NAME} PRIVATE ${LINK_OPTIONS})
set_target_properties(${TARGET_NAME} PROPERTIES LINK_DEPENDS ${LINKER_SCRIPT})
target_link_libraries(${TARGET_NAME} PRIVATE rdk-libc)
target_compile_options(${TARGET_NAME} PRIVATE -m32 -mno-sse)
target_link_options(${TARGET_NAME} PRIVATE -m32)
target_include_directories(${TARGET_NAME} PRIVATE ${x86_INCLOUDE_DIR})

include(MakeBootGrubTarget)

make_boot_grub_target(${TARGET_NAME} ${TARGET_NAME}.iso)
