add_library(picogame INTERFACE)

target_sources(picogame INTERFACE 
    ${CMAKE_CURRENT_LIST_DIR}/picogame.c
    #${CMAKE_CURRENT_LIST_DIR}/picoscreen.cpp
    ${CMAKE_CURRENT_LIST_DIR}/picogame_sdk/screen/screen.c
    ${CMAKE_CURRENT_LIST_DIR}/picogame_sdk/screen/ili9341.c
    ${CMAKE_CURRENT_LIST_DIR}/picogame_sdk/input/input.cpp)

target_include_directories(picogame INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/
    ${CMAKE_CURRENT_LIST_DIR}/picogame_sdk/
    ${CMAKE_CURRENT_LIST_DIR}/picogame_sdk/screen/
    ${CMAKE_CURRENT_LIST_DIR}/picogame_sdk/input)

target_link_libraries(usermod INTERFACE picogame)