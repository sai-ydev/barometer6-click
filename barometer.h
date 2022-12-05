/**
 * Barometer 6 drivers.
 *
 * SPDX-License-Identifier: MIT
 **/

/*
* @file barometer6.h
  @brief This file contains API for the barometer6 click drivers
*/

#ifndef BAROMETER6_H
#define BAROMETER6_H

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief 2SMPB-02E Chip ID
 * @details Specified chip id of the sensor on the barometer 6 click
*/
#define BAROMETER6_RESET            _u(0XE0)
#define BAROMETER6_CHIP_ID          _u(0xD1)


/**
 * @brief Barometer 6 software reset command.
 * @details Specified software reset command of Barometer 6 Click driver.
 */
#define BAROMETER6_CMD_RESET       _u(0xE6)

/**
 * @brief Barometer 6 click device address setting
 * @details Specified settings for I2C device address selection of Barometer6
 * Click Driver
*/
#define BAROMETER6_DEV_ADDR_LOW     _u(0x70)
#define BAROMETER6_DEV_ADDR_HIGH    _u(0x56)

#ifdef __cplusplus
}
#endif
#endif