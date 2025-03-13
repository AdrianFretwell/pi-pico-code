cmake_minimum_required(VERSION 3.12)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

project(rotenctest)

# Initialize the SDK
pico_sdk_init()

add_executable(rotenctest
    rotaryencoder.c rotaryencoder.h
    main.c
    )

# Enable USB stdio and disable UART stdio
#pico_enable_stdio_usb(vfo1 1)
#pico_enable_stdio_uart(vfo 0)

# pull in common dependencies
target_link_libraries(rotenctest
    pico_stdlib
    hardware_gpio
    )

# create map/bin/hex file etc.
pico_add_extra_outputs(rotenctest)
