set(PROJECT PicoGame)
cmake_minimum_required(VERSION 3.15)
project(${PROJECT} C CXX ASM)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
pico_sdk_init()

#target_include_directories(display)
include_directories(display)

add_executable(${PROJECT} main.c display/display.c)
target_link_libraries(${PROJECT} pico_stdlib hardware_spi)

pico_add_extra_outputs(${PROJECT})
pico_enable_stdio_usb(${PROJECT} 1)
pico_enable_stdio_uart(${PROJECT} 0)