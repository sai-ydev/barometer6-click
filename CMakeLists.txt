add_executable(barometer6
        barometer6.c
        )

# pull in common dependencies and additional i2c hardware support
target_link_libraries(barometer6 pico_stdlib hardware_i2c)

pico_enable_stdio_usb(barometer6 1)

# create map/bin/hex file etc.
pico_add_extra_outputs(barometer6)

# add url via pico_set_program_url
example_auto_set_url(barometer6)
