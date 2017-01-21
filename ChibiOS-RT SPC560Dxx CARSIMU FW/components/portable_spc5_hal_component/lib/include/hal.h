/*
    ChibiOS/RT - Copyright (C) 2006-2013 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/**
 * @file    hal.h
 * @brief   HAL subsystem header.
 *
 * @addtogroup HAL
 * @{
 */

#ifndef _HAL_H_
#define _HAL_H_

#include "osal.h"
#include "board.h"
#include "halconf.h"

#include "hal_lld.h"

/* Abstract interfaces.*/
#include "hal_streams.h"
#include "hal_channels.h"
#include "hal_queues.h"

/* Shared headers.*/
//#include "io_block.h"
//#include "mmcsd.h"

/* Normal drivers.*/
#include "tm.h"
#include "pal.h"
#include "adc.h"
#include "can.h"
//#include "ext.h"
//#include "gpt.h"
//#include "i2c.h"
#include "icu.h"
//#include "mac.h"
#include "pwm.h"
//#include "rtc.h"
#include "serial.h"
//#include "sdc.h"
#include "spi.h"
//#include "uart.h"
//#include "usb.h"

/* Complex drivers.*/
//#include "mmc_spi.h"
//#include "serial_usb.h"

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

#if HAL_IMPLEMENTS_COUNTERS || defined(__DOXYGEN__)
/**
 * @name    Time conversion utilities for the realtime counter
 * @{
 */
/**
 * @brief   Seconds to realtime ticks.
 * @details Converts from seconds to realtime ticks number.
 * @note    The result is rounded upward to the next tick boundary.
 *
 * @param[in] sec       number of seconds
 * @return              The number of ticks.
 *
 * @api
 */
#define S2RTT(sec) (halGetCounterFrequency() * (sec))

/**
 * @brief   Milliseconds to realtime ticks.
 * @details Converts from milliseconds to realtime ticks number.
 * @note    The result is rounded upward to the next tick boundary.
 *
 * @param[in] msec      number of milliseconds
 * @return              The number of ticks.
 *
 * @api
 */
#define MS2RTT(msec) (((halGetCounterFrequency() + 999UL) / 1000UL) * (msec))

/**
 * @brief   Microseconds to realtime ticks.
 * @details Converts from microseconds to realtime ticks number.
 * @note    The result is rounded upward to the next tick boundary.
 *
 * @param[in] usec      number of microseconds
 * @return              The number of ticks.
 *
 * @api
 */
#define US2RTT(usec) (((halGetCounterFrequency() + 999999UL) / 1000000UL) * \
                      (usec))

/**
 * @brief   Realtime ticks to seconds to.
 * @details Converts from realtime ticks number to seconds.
 *
 * @param[in] ticks     number of ticks
 * @return              The number of seconds.
 *
 * @api
 */
#define RTT2S(ticks) ((ticks) / halGetCounterFrequency())

/**
 * @brief   Realtime ticks to milliseconds.
 * @details Converts from realtime ticks number to milliseconds.
 *
 * @param[in] ticks     number of ticks
 * @return              The number of milliseconds.
 *
 * @api
 */
#define RTT2MS(ticks) ((ticks) / (halGetCounterFrequency() / 1000UL))

/**
 * @brief   Realtime ticks to microseconds.
 * @details Converts from realtime ticks number to microseconds.
 *
 * @param[in] ticks     number of ticks
 * @return              The number of microseconds.
 *
 * @api
 */
#define RTT2US(ticks) ((ticks) / (halGetCounterFrequency() / 1000000UL))
/** @} */

/**
 * @name    Macro Functions
 * @{
 */
/**
 * @brief   Returns the current value of the system free running counter.
 * @note    This is an optional service that could not be implemented in
 *          all HAL implementations.
 * @note    This function can be called from any context.
 *
 * @return              The value of the system free running counter of
 *                      type halrtcnt_t.
 *
 * @special
 */
#define halGetCounterValue() hal_lld_get_counter_value()

/**
 * @brief   Realtime counter frequency.
 * @note    This is an optional service that could not be implemented in
 *          all HAL implementations.
 * @note    This function can be called from any context.
 *
 * @return              The realtime counter frequency of type halclock_t.
 *
 * @special
 */
#define halGetCounterFrequency() hal_lld_get_counter_frequency()
/** @} */
#endif /* HAL_IMPLEMENTS_COUNTERS */

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
  void halInit(void);
#if HAL_IMPLEMENTS_COUNTERS
  bool halIsCounterWithin(halrtcnt_t start, halrtcnt_t end);
  void halPolledDelay(halrtcnt_t ticks);
#endif /* HAL_IMPLEMENTS_COUNTERS */
#ifdef __cplusplus
}
#endif

#endif /* _HAL_H_ */

/** @} */
