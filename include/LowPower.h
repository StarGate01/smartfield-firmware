/**
 * @file LowPower.h
 * @author Christoph Honal
 * @brief Defines low power helper functions
 * @version 0.1
 * @date 2021-04-12
 */

#include "Arduino.h"

#ifndef LOW_POWER_H
#define LOW_POWER_H

/**
 * @brief Wakes the device from sleep mode
 * 
 */
extern void wakeUp();

/**
 * @brief Sends the device to sleep mode
 * 
 * @param sleeptime For how many ms to sleep
 */
extern void lowPowerSleep(uint32_t sleeptime);

#endif