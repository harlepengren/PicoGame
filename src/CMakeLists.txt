set(PROJECT PicoGame)
cmake_minimum_required(VERSION 3.15)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
project(${PROJECT} C CXX ASM)

pico_sdk_init()

add_subdirectory(FatFs_SPI build)

add_executable(${PROJECT} main.cpp ili9341/ili9341.c ili9341/mode2.c ili9341/image.cpp hw_config.c setup.cpp)

target_include_directories(${PROJECT} PRIVATE ${CMAKE_SOURCE_DIR}/ili9341)

target_link_libraries(${PROJECT} pico_stdlib hardware_spi hardware_flash pico_malloc pico_mem_ops pico_multicore FatFs_SPI)

pico_set_program_name(${PROJECT} "PicoGame")
pico_set_program_version(${PROJECT} "0.1")

pico_add_extra_outputs(${PROJECT})
pico_enable_stdio_usb(${PROJECT} 0)
pico_enable_stdio_uart(${PROJECT} 1)