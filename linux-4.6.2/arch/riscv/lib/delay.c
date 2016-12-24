#include <linux/delay.h>
#include <linux/param.h>
#include <linux/timex.h>
#include <linux/export.h>

void __delay(unsigned long cycles)
{
	cycle_t t0 = get_cycles();
	while ((unsigned long)(get_cycles() - t0) < cycles)
		cpu_relax();
}

void udelay(unsigned long usecs)
{
	u64 dt = (u64)usecs * timebase;

	__delay(do_div(dt, 1000000UL));
	//__delay((unsigned long)(((u64)usecs * timebase) / 1000000UL));

}
EXPORT_SYMBOL(udelay);

void ndelay(unsigned long nsecs)
{
	u64 dt = (u64)nsecs * timebase;

	__delay(do_div(dt, 1000000000UL));
	//	__delay((unsigned long)(((u64)nsecs * timebase) / 1000000000UL));
}
EXPORT_SYMBOL(ndelay);
