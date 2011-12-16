#if !defined(TIMER_H)
#define TIMER_H
#include <time.h>
#ifdef __MACH__
	#include <sys/time.h>
#endif

using namespace std;

class Timer
{
	private:
		timespec start;
		timespec end;
	public:
		void start_clock(void);
		void end_clock(void);
		timespec diff(void);
};

#endif // TIMER_H

