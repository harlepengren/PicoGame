set(PROJECT PicoGame_sdk)
cmake_minimum_required(VERSION 3.15)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(${PROJECT} C CXX ASM)

#pico_sdk_init()

add_subdirectory(FatFs_SPI build)
add_subdirectory(screen)
add_subdirectory(input)

add_library(${PROJECT} INTERFACE)

target_sources(${PROJECT} INTERFACE hw_config.c setup.cpp)

target_link_libraries(${PROJECT} INTERFACE pico_stdlib hardware_spi hardware_flash hardware_timer
    pico_malloc pico_mem_ops pico_multicore FatFs_SPI screen input)

#pico_set_program_name(${PROJECT} "PicoGame")
#pico_set_program_version(${PROJECT} "0.1")

#pico_add_extra_outputs(${PROJECT})
#pico_enable_stdio_usb(${PROJECT} 0)
#pico_enable_stdio_uart(${PROJECT} 1)