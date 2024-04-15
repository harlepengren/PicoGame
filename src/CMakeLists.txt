set(PROJECT PicoGame)
cmake_minimum_required(VERSION 3.15)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
project(${PROJECT} C CXX ASM)

pico_sdk_init()

add_executable(${PROJECT} main.cpp ili9341/ili9341.c ili9341/mode2.c ili9341/image.cpp)

target_include_directories(${PROJECT} PRIVATE ${CMAKE_SOURCE_DIR}/ili9341)

target_link_libraries(${PROJECT} pico_stdlib hardware_spi pico_malloc pico_mem_ops)

pico_add_extra_outputs(${PROJECT})
pico_enable_stdio_usb(${PROJECT} 1)
pico_enable_stdio_uart(${PROJECT} 0)