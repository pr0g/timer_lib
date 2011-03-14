/* timer.h  -  v0.1  -  Public Domain  -  2011 Mattias Jansson / Rampant Pixels
 * 
 * This library provides a cross-platform interface to measure
 * elapsed time with (at least) millisecond accuracy.
 *
 * This library is put in the public domain; you can redistribute
 * it and/or modify it without any restrictions.
 *
 * VERSION HISTORY
 *
 * 0.1  (2011-03-15)  Initial release
 */

#pragma once

/*! \file timer.h
    Timer measuring deltatimes */

#if TIMER_COMPILE
#define TIMER_API
#else
#if __cplusplus
#define TIMER_API extern "C"
#else
#define TIMER_API extern
#endif
#endif

//! Deltaticks type
#if defined( _WIN32 ) || defined( _WIN64 )
typedef unsigned __int64 tick_t;
#else
#include <stdint.h>
typedef uint64_t tick_t;
#endif

//! Deltatime type (float or double)
typedef float deltatime_t;
//typedef double deltatime_t;

//! Timer type
typedef enum 
{
	//! High resolution
	TIMER_HIGHRESOLUTION,

	//! Stable
	TIMER_STABLE
} timer_type;

//! Timer
typedef struct
{
	//! Type
	timer_type     type;

	//! Old clock
	tick_t         clock;

	//! Reference
	tick_t         ref;

	//! Ticks per second
	tick_t         freq;

	//! Multiplier ( 1 / frequency )
	deltatime_t    oofreq;
} timer;


/*! Initialize timer library */
TIMER_API void           timer_lib_initialize();

/*! Shutdown timer library */
TIMER_API void           timer_lib_shutdown();

/*! Initialize timer and reset
    \param t             Timer
    \param type          Type */
TIMER_API void           timer_initialize( timer* t, timer_type type );

/*! Reset timer
    \param t             Timer */
TIMER_API void           timer_reset( timer* t );

/*! Get elapsed time since last reset, and optionally reset timer
    \param t             Timer
    \param reset         Reset flag (reset if not zero)
    \return              Number of seconds elapsed */
TIMER_API deltatime_t    timer_elapsed( timer* t, int reset );

/*! Get elapsed ticks since last reset, and optionally reset timer
    \param t             Timer
    \param reset         Reset flag (reset if not zero)
    \return              Number of ticks elapsed */
TIMER_API tick_t         timer_elapsed_ticks( timer* t, int reset );

/*! Get timer frequency, as number of ticks per second
    \param t             Timer
    \return              Ticks per second */
TIMER_API tick_t         timer_ticks_per_second( timer* t );

/*! Get current time, in ticks of system-specific frequency. Measured from some system-specific base time and not in sync with other sytem timestamps
    \return              Current timestamp, in ticks */
TIMER_API tick_t         timer_current();

/*! Get frequency of current time ticks
    \return              Number of ticks per second for timer_current function */
TIMER_API tick_t         timer_current_ticks_per_second();

/*! Get system time, in milliseconds since the epoch (UNIX time)
    \return  Current timestamp, in milliseconds */
TIMER_API tick_t         timer_system();
