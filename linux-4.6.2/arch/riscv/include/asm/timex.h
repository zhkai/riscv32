#ifndef _ASM_RISCV_TIMEX_H
#define _ASM_RISCV_TIMEX_H

#include <asm/param.h>

#define CLOCK_TICK_RATE (HZ * 100UL)

typedef unsigned long cycles_t;

static inline cycles_t get_cycles(void)
{
#ifdef __riscv64
	cycles_t n;
	__asm__ __volatile__ (
		"rdtime %0"
		: "=r" (n));
	return n;
#else
	u32 lo, hi, tmp;
	__asm__ __volatile__ (
		"1:\n"
		"rdtimeh %0\n"
		"rdtime %1\n"
		"rdtimeh %2\n"
		"bne %0, %2, 1b"
		: "=&r" (hi), "=&r" (lo), "=&r" (tmp));
	return ((u64)hi << 32) | lo;
#endif
}

#define ARCH_HAS_READ_CURRENT_TIMER

static inline int read_current_timer(unsigned long *timer_val)
{
	*timer_val = get_cycles();
	return 0;
}

#endif /* _ASM_RISCV_TIMEX_H */
