#ifndef _ASM_RISCV_MMU_CONTEXT_H
#define _ASM_RISCV_MMU_CONTEXT_H

#include <asm-generic/mm_hooks.h>

#include <linux/mm.h>
#include <linux/sched.h>
#include <asm/tlbflush.h>

static inline void enter_lazy_tlb(struct mm_struct *mm,
	struct task_struct *task)
{
}

/* Initialize context-related info for a new mm_struct */
static inline int init_new_context(struct task_struct *task,
	struct mm_struct *mm)
{
	return 0;
}

static inline void destroy_context(struct mm_struct *mm)
{
}

static inline void switch_mm(struct mm_struct *prev,
	struct mm_struct *next, struct task_struct *task)
{
	if (likely(prev != next)) {
		csr_write(sptbr, virt_to_pfn(next->pgd));
		local_flush_tlb_all();
	}
}

static inline void activate_mm(struct mm_struct *prev,
			       struct mm_struct *next)
{
	switch_mm(prev, next, NULL);
}

static inline void deactivate_mm(struct task_struct *task,
	struct mm_struct *mm)
{
}

#endif /* _ASM_RISCV_MMU_CONTEXT_H */
