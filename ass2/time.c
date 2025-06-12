// Implementation of the time module

// !!! DO NOT MODIFY THIS FILE !!!

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "time.h"

struct time timeNew(int hour, int minute) {
	return (struct time){.hour = hour, .minute = minute};
}

struct time timeAdd(struct time t, int minutes) {
	minutes = ((minutes % MINUTES_PER_DAY) + MINUTES_PER_DAY) %
		MINUTES_PER_DAY;
	int hours = minutes / MINUTES_PER_HOUR;
	minutes = minutes % MINUTES_PER_HOUR;

	t.minute += minutes;
	if (t.minute >= MINUTES_PER_HOUR) {
		t.hour++;
		t.minute -= MINUTES_PER_HOUR;
	}
	t.hour = (t.hour + hours) % HOURS_PER_DAY;
	return t;
}

int timeDiff(struct time t1, struct time t2) {
	int mins1 = t1.hour * MINUTES_PER_HOUR + t1.minute;
	int mins2 = t2.hour * MINUTES_PER_HOUR + t2.minute;
	return (mins2 + MINUTES_PER_DAY - mins1) % MINUTES_PER_DAY;
}

bool timeEquals(struct time t1, struct time t2) {
	return t1.hour == t2.hour && t1.minute == t2.minute;
}

