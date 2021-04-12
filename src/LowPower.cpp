/**
 * @file LowPower.cpp
 * @author Christoph Honal
 * @brief Implements the functions defined in LowPower.h
 * @version 0.1
 * @date 2021-04-12
 */

#include "LowPower.h"

TimerEvent_t sleepTimer;
bool sleepTimerExpired;

void wakeUp()
{
    sleepTimerExpired = true;
}

void lowPowerSleep(uint32_t sleeptime)
{
    sleepTimerExpired = false;
    TimerInit(&sleepTimer, &wakeUp);
    TimerSetValue(&sleepTimer, sleeptime);
    TimerStart(&sleepTimer);

    //Low power handler also gets interrupted by other timers
    //So wait until our timer had expired
    while (!sleepTimerExpired) lowPowerHandler();
    TimerStop( &sleepTimer );
}
