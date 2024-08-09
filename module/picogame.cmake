add_library(picogame INTERFACE)

target_sources(picogame INTERFACE 
    ${CMAKE_CURRENT_LIST_DIR}/picogame.c
    #${CMAKE_CURRENT_LIST_DIR}/picoscreen.cpp
    ${CMAKE_CURRENT_LIST_DIR}/picogame_sdk/screen/screen.c
    ${CMAKE_CURRENT_LIST_DIR}/picogame_sdk/screen/ili9341.c
    ${CMAKE_CURRENT_LIST_DIR}/picogame_sdk/input/input.cpp
    ${CMAKE_CURRENT_LIST_DIR}/picogame_sdk/image/image.c
    ${CMAKE_CURRENT_LIST_DIR}/picogame_sdk/image/hw_config.c
    ${CMAKE_CURRENT_LIST_DIR}/picogame_sdk/sdcard/FatFs_SPI/src/f_util.c)

remove_definitions(-Werror)

target_include_directories(picogame INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/
    ${CMAKE_CURRENT_LIST_DIR}/picogame_sdk/
    ${CMAKE_CURRENT_LIST_DIR}/picogame_sdk/screen/
    ${CMAKE_CURRENT_LIST_DIR}/picogame_sdk/input
    ${CMAKE_CURRENT_LIST_DIR}/picogame_sdk/image
    ${CMAKE_CURRENT_LIST_DIR}/picogame_sdk/sdcard/FatFs_SPI/ff15/source/
    ${CMAKE_CURRENT_LIST_DIR}/picogame_sdk/sdcard/FatFs_SPI/sd_driver/
    ${CMAKE_CURRENT_LIST_DIR}/picogame_sdk/sdcard/FatFs_SPI/include)

target_link_libraries(usermod INTERFACE picogame)