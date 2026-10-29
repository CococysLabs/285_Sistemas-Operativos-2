#include <linux/kernel.h>
#include <linux/kernel_stat.h>
#include <linux/mm.h>
#include <linux/module.h>
#include <linux/sched/signal.h>
#include <linux/sysinfo.h>

struct proceso_rss {
	pid_t pid;
	char comm[TASK_COMM_LEN];
	unsigned long rss_kb;
};

static int __init met_init(void)
{
	struct sysinfo info;
	struct proceso_rss top[5] = {};
	struct task_struct *p;
	u64 user = 0, system = 0, idle = 0;
	int cpu, k;

	for_each_possible_cpu(cpu) {
		user += kcpustat_cpu(cpu).cpustat[CPUTIME_USER];
		system += kcpustat_cpu(cpu).cpustat[CPUTIME_SYSTEM];
		idle += kcpustat_cpu(cpu).cpustat[CPUTIME_IDLE];
	}
	pr_info("met: cpu user=%llu system=%llu idle=%llu (ticks)\n",
		user, system, idle);

	si_meminfo(&info);
	pr_info("met: mem total=%lu KB libre=%lu KB\n",
		info.totalram << (PAGE_SHIFT - 10),
		info.freeram << (PAGE_SHIFT - 10));

	rcu_read_lock();
	for_each_process(p) {
		unsigned long rss_kb;
		int pos = 4;

		if (!p->mm)
			continue;
		rss_kb = get_mm_rss(p->mm) << (PAGE_SHIFT - 10);
		if (rss_kb <= top[4].rss_kb)
			continue;
		while (pos > 0 && rss_kb > top[pos - 1].rss_kb) {
			top[pos] = top[pos - 1];
			pos--;
		}
		top[pos].pid = p->pid;
		top[pos].rss_kb = rss_kb;
		get_task_comm(top[pos].comm, p);
	}
	rcu_read_unlock();

	for (k = 0; k < 5; k++)
		if (top[k].pid)
			pr_info("met: %d %s %lu KB\n", top[k].pid,
				top[k].comm, top[k].rss_kb);
	return 0;
}

static void __exit met_exit(void)
{
}

module_init(met_init);
module_exit(met_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Laboratorio SO2 - USAC");
MODULE_DESCRIPTION("Metricas de CPU, memoria y procesos");
