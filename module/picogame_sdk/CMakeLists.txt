include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

add_library(picogame_sdk INTERFACE)

#pico_sdk_init()
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/FatFs_SPI)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/screen)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/input)

target_sources(picogame_sdk INTERFACE ${CMAKE_CURRENT_LIST_DIR}/hw_config.c ${CMAKE_CURRENT_LIST_DIR}/setup.cpp)

target_link_libraries(picogame_sdk INTERFACE pico_stdlib hardware_spi hardware_flash hardware_timer
    pico_malloc pico_mem_ops pico_multicore FatFs_SPI screen input)

#pico_add_extra_outputs(${PROJECT})
#pico_enable_stdio_usb(${PROJECT} 0)
#pico_enable_stdio_uart(${PROJECT} 1)