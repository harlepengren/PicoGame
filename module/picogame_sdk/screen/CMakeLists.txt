add_library(screen INTERFACE)

target_sources(screen INTERFACE
    screen.cpp
    ili9341.c
    )

target_link_libraries(screen INTERFACE
        hardware_spi
        pico_stdlib
        pico_mem_ops
)
