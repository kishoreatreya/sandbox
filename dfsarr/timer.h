#ifndef _TIMER_H_
#define _TIMER_H_

/**
 * @file timer.h
 *
 * @brief This file contains a macro defintion used to retrieve
 *        the current time of day
 *
 * The GET_TIME(x) macro uses, the gettimeofday() function to
 * get the current timestamp. It will be used to calculate
 * time elapsed for an operation
 *
 */

#include <sys/time.h>

/**
 * @def USEC_PER_SEC
 *
 * @brief Number of microseconds in one second (1 million)
 *
 */
#define USEC_PER_SEC 1000000.0

/**
 * @def GET_TIME
 *
 * @brief Macro used to retrieve the current time
 *
 * This macro uses the sys/time library to retrieve the current
 * time stamp.
 *
 * @param x
 *
 */
#define GET_TIME(x)                             \
{                                               \
    struct timeval t;                           \
    gettimeofday(&t, NULL);                     \
    x = t.tv_sec + t.tv_usec / USEC_PER_SEC;    \
}



#endif // _TIMER_H_
