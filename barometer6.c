/**
 * Barometer 6 drivers.
 *
 * SPDX-License-Identifier: MIT
 **/

#include <stdio.h>

#include "hardware/i2c.h"
#include "pico/binary_info.h"
#include "pico/stdlib.h"
#include "barometer.h"

#define ADDRESS BAROMETER6_DEV_ADDR_LOW

#define DUMMY  0x00

#define RST 13
#define ON  1
#define OFF 0

 /* Example code to talk to a Barometer6 click

    Board used: https://www.sparkfun.com/products/18721

    Connections on Sparkfun RP2040 MikroBus board:

    I2C_1 SDA_PIN (on Pico this is GP6 (pin 9)) -> SDA on BMP280
    board
    I2C_1 SCL_PIN (on Pico this is GP7 (pin 10)) -> SCL on
    BMP280 board
    
 */

int write_reg(uint8_t reg, uint8_t data){
    uint8_t reg_data[] = {reg, data};
    int num_bytes = i2c_write_blocking(i2c_default, BAROMETER6_DEV_ADDR_LOW, reg_data, 2, false);
    return num_bytes;
}

void read_reg(uint8_t* reg, uint8_t* data){
    i2c_write_blocking(i2c_default, ADDRESS, reg, 1, true);
    i2c_read_blocking(i2c_default, ADDRESS, data, 1, true);
}

void read_chip_id(uint8_t* reg_data)
{
    uint8_t reg = BAROMETER6_CHIP_ID;
    read_reg(&reg, reg_data);
}

void reset_barometer(){
    gpio_put(RST, ON);
    sleep_us(100);
    gpio_put(RST, OFF);
    sleep_ms(10);
}

int main() {
    
    uint8_t chip_id;
    stdio_init_all();

    while(!stdio_usb_connected()){
        sleep_ms(10);
    }

#if !defined(i2c_default) || !defined(PICO_DEFAULT_I2C_SDA_PIN) || !defined(PICO_DEFAULT_I2C_SCL_PIN)
    #warning i2c / barometer6 example requires a board with I2C pins
        puts("Default I2C pins were not defined");
#else
    // useful information for picotool
    bi_decl(bi_2pins_with_func(PICO_DEFAULT_I2C_SDA_PIN, PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C));
    bi_decl(bi_program_description("Barometer 6 click for the RP2040!\n"));

    printf("Hello, BMP280! Reading temperaure and pressure values from sensor...\n");

    // I2C is "open drain", pull ups to keep signal high when no data is being sent
    i2c_init(i2c_default, 100 * 1000);
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_init(RST);
    gpio_set_dir(RST, GPIO_OUT);

    reset_barometer();
    read_chip_id(&chip_id);

    printf("Chip ID = %02X", chip_id);


    sleep_ms(250); // sleep so that data polling and register update don't collide
    while (1) {
        
        // poll every 500ms
        sleep_ms(500);
    }

#endif
    return 0;
}
