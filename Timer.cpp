#if !defined(TIMER_CPP)
#define TIMER_CPP

#include "Timer.h"

void Timer::start_clock(){
#ifdef __MACH__
	timeval tmp;
	gettimeofday(&tmp, NULL);
	start.tv_sec = tmp.tv_sec;
	start.tv_nsec = tmp.tv_usec * 1000;
#else
	clock_gettime(CLOCK_REALTIME, &start);
#endif
}

void Timer::end_clock(){
#ifdef __MACH__
	timeval tmp;
	gettimeofday(&tmp, NULL);
	end.tv_sec = tmp.tv_sec;
	end.tv_nsec = tmp.tv_usec * 1000;
#else
	clock_gettime(CLOCK_REALTIME, &end);
#endif
}

timespec Timer::diff(){
	timespec temp;
	if ((end.tv_nsec-start.tv_nsec)<0) {
		temp.tv_sec = end.tv_sec-start.tv_sec-1;
		temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
	} else {
		temp.tv_sec = end.tv_sec-start.tv_sec;
		temp.tv_nsec = end.tv_nsec-start.tv_nsec;
	}
	return temp;
}

#endif // TIMER_CPP

