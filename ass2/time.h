// Interface to the time module

// !!! DO NOT MODIFY THIS FILE !!!

#ifndef TIME_H
#define TIME_H

#include <stdbool.h>

#define MINUTES_PER_HOUR 60
#define HOURS_PER_DAY    24
#define MINUTES_PER_DAY  (MINUTES_PER_HOUR * HOURS_PER_DAY)

struct time {
    int hour;   // between 0 and HOURS_PER_DAY - 1 (inclusive)
    int minute; // between 0 and MINUTES_PER_HOUR - 1 (inclusive)
};

/**
 * Returns a new time containing the given hour and minute.
 * Assumes that `hour` is between 0 and (HOURS_PER_DAY - 1) inclusive
 * and `minute` is between 0 and (MINUTES_PER_HOUR - 1) inclusive.
 */
struct time timeNew(int hour, int minute);

/**
 * Returns a new time which is the result of adding the given number of
 * minutes to the given time.
 * `minutes` can be any integer, including negative, which results in
 * subtracting minutes instead.
 * Assumes that `t` is a valid time.
 */
struct time timeAdd(struct time t, int minutes);

/**
 * Returns the number of minutes elapsed in the time period from `start`
 * to `end`. Always returns integer between 0 and (MINUTES_PER_DAY - 1).
 * Assumes that `start` and `end` are valid times.
 */
int timeDiff(struct time start, struct time end);

/**
 * Returns true if the two given times are equal.
 */
bool timeEquals(struct time t1, struct time t2);

#endif
