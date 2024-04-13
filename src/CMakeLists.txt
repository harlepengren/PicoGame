set(PROJECT PicoGame)
cmake_minimum_required(VERSION 3.15)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
project(${PROJECT} VERSION 0.1
                   DESCRIPTION "A simple game engine for the raspberry pico."
                   LANGUAGES C CXX ASM)

pico_sdk_init()

add_library(ili9341 ili9341/ili9341.c)
add_library(mode2 ili9341/mode2.c)

add_executable(${PROJECT} main.cpp)

target_link_libraries(${PROJECT} ili9341 mode2 pico_stdlib hardware_spi)

pico_add_extra_outputs(${PROJECT})
pico_enable_stdio_usb(${PROJECT} 1)
pico_enable_stdio_uart(${PROJECT} 0)