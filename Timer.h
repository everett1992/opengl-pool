/* Caleb Everett
 * Graphics Final
 *
 * Header for Timer
 * Used to mesure elapes time
 */

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
		timespec diff(void); // return elapsed time in timespec format
		double seconds(void); // return elapsed time as fractional seconds
};

#endif // TIMER_H

