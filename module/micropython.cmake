# Create an INTERFACE library for our C module.
add_library(picogame INTERFACE)

include(${CMAKE_CURRENT_LIST_DIR}/../src/picogame_sdk.cmake)

# Add our source files to the lib
target_sources(picogame INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/picogame.c #${CMAKE_CURRENT_LIST_DIR}/simplemath.c
)

# Add the current directory as an include directory.
target_include_directories(picogame INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
)

# Link our INTERFACE library to the usermod target.
target_link_libraries(usermod INTERFACE picogame PicoGame_sdk)
