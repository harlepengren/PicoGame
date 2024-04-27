add_library(screen INTERFACE)
target_sources(screen INTERFACE
    screen.cpp
    ili9341.c
    )
#target_include_directories(FatFs_SPI INTERFACE
#    ff15/source
#    sd_driver
#    include
#)
target_link_libraries(screen INTERFACE
        hardware_spi
        pico_stdlib
        pico_mem_ops
)
