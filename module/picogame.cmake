add_library(usermod_picogame INTERFACE)

message(${CMAKE_CURRENT_LIST_DIR})
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/picogame_sdk build)

target_sources(usermod_picogame INTERFACE picogame.c picoscreen.cpp)

target_link_libraries(usermod INTERFACE picogame_sdk usermod_picogame)