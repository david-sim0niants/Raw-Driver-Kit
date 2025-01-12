set(TARGET_NAME rdk-libc)
add_library(${TARGET_NAME} INTERFACE)
target_sources(${TARGET_NAME} INTERFACE stdlib.c string.c)
target_include_directories(${TARGET_NAME} INTERFACE include)
