set(PROJECT PicoGame_sdk)
cmake_minimum_required(VERSION 3.15)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(${PROJECT} C CXX ASM)

#pico_sdk_init()
message(STATUS "picogame_sdk including directories ----- ${CMAKE_CURRENT_LIST_DIR}")
include_directories(${CMAKE_CURRENT_LIST_DIR}/FatFs_SPI)
include_directories(${CMAKE_CURRENT_LIST_DIR}/screen)
include_directories(${CMAKE_CURRENT_LIST_DIR}/input)
message(STATUS "added all directories")

add_library(${PROJECT} INTERFACE)

target_sources(${PROJECT} INTERFACE ${CMAKE_CURRENT_LIST_DIR}/hw_config.c ${CMAKE_CURRENT_LIST_DIR}/setup.cpp)

target_link_libraries(${PROJECT} INTERFACE pico_stdlib hardware_spi hardware_flash hardware_timer
    pico_malloc pico_mem_ops pico_multicore FatFs_SPI screen input)

#pico_set_program_name(${PROJECT} "PicoGame")
#pico_set_program_version(${PROJECT} "0.1")

#pico_add_extra_outputs(${PROJECT})
#pico_enable_stdio_usb(${PROJECT} 0)
#pico_enable_stdio_uart(${PROJECT} 1)