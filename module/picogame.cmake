add_library(picogame INTERFACE)

target_sources(picogame INTERFACE 
    ${CMAKE_CURRENT_LIST_DIR}/picogame.c
    #${CMAKE_CURRENT_LIST_DIR}/picoscreen.cpp
    ${CMAKE_CURRENT_LIST_DIR}/picogame_sdk/screen/screen.c
    ${CMAKE_CURRENT_LIST_DIR}/picogame_sdk/screen/ili9341.c
    ${CMAKE_CURRENT_LIST_DIR}/picogame_sdk/input/input.cpp
    ${CMAKE_CURRENT_LIST_DIR}/picogame_sdk/image/image.c
    ${CMAKE_CURRENT_LIST_DIR}/picogame_sdk/image/hw_config.c
    #${CMAKE_CURRENT_LIST_DIR}/picogame_sdk/FatFs_SPI/ff15/source/ff.c
    ${CMAKE_CURRENT_LIST_DIR}/../no-OS-FatFS-SD-SDIO-SPI-RPi-Pico/src/src/f_util.c
    #${CMAKE_CURRENT_LIST_DIR}/../no-OS-FatFS-SD-SDIO-SPI-RPI-Pico/src/my_debug.c
    ${CMAKE_CURRENT_LIST_DIR}/../no-OS-FatFS-SD-SDIO-SPI-RPi-Pico/src/sd_driver/sd_card.c)

#set_source_files_properties(${CMAKE_CURRENT_LIST_DIR}/picogame_sdk/FatFs_SPI/sd_driver/sd_card.c 
#    PROPERTIES COMPILE_OPTIONS "-Wno-unused-parameter;-Wno-missing-field-initializer;-Wno-unused-variable")

remove_definitions(-Werror)

target_include_directories(picogame INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/
    ${CMAKE_CURRENT_LIST_DIR}/picogame_sdk/
    ${CMAKE_CURRENT_LIST_DIR}/picogame_sdk/screen/
    ${CMAKE_CURRENT_LIST_DIR}/picogame_sdk/input
    ${CMAKE_CURRENT_LIST_DIR}/picogame_sdk/image
    ${CMAKE_CURRENT_LIST_DIR}/../no-OS-FatFS-SD-SDIO-SPI-RPi-Pico/src/ff15/source/
    ${CMAKE_CURRENT_LIST_DIR}/../no-OS-FatFS-SD-SDIO-SPI-RPi-Pico/src/sd_driver/
    ${CMAKE_CURRENT_LIST_DIR}/../no-OS-FatFS-SD-SDIO-SPI-RPi-Pico/src/include)

target_link_libraries(usermod INTERFACE picogame)