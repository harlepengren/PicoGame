add_library(input INTERFACE)

target_sources(input INTERFACE
    input.cpp
    )

target_link_libraries(input INTERFACE
        hardware_gpio
        pico_stdlib
)
