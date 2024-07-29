add_library(image INTERFACE)

target_sources(image INTERFACE
    image.c
    )

target_link_libraries(input INTERFACE
        hardware_gpio
        pico_stdlib
)
