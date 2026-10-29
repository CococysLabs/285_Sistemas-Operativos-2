#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/proc_fs.h>
#include <linux/sched/signal.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>

static DEFINE_MUTEX(cfg_lock);
static int umbral_mb = 256;

static int so2_show(struct seq_file *m, void *v)
{
	struct sysinfo info;
	struct task_struct *p;
	unsigned long libre_mb;
	int procesos = 0, umbral;

	(void)v;
	si_meminfo(&info);
	libre_mb = info.freeram >> (20 - PAGE_SHIFT);
	rcu_read_lock();
	for_each_process(p)
		procesos++;
	rcu_read_unlock();
	mutex_lock(&cfg_lock);
	umbral = umbral_mb;
	mutex_unlock(&cfg_lock);
	seq_printf(m, "{\"total_mb\":%lu,\"libre_mb\":%lu,\"procesos\":%d,"
		   "\"umbral_mb\":%d,\"alerta\":%s}\n",
		   info.totalram >> (20 - PAGE_SHIFT), libre_mb, procesos, umbral,
		   libre_mb < (unsigned long)umbral ? "true" : "false");
	return 0;
}

static ssize_t so2_write(struct file *file, const char __user *user_buf,
			 size_t len, loff_t *offset)
{
	char buf[16];
	int value;

	(void)file;
	(void)offset;
	if (len == 0 || len >= sizeof(buf))
		return -EINVAL;
	if (copy_from_user(buf, user_buf, len))
		return -EFAULT;
	buf[len] = '\0';
	if (kstrtoint(strim(buf), 10, &value) || value < 0)
		return -EINVAL;
	mutex_lock(&cfg_lock);
	umbral_mb = value;
	mutex_unlock(&cfg_lock);
	return len;
}

static int so2_open(struct inode *inode, struct file *file)
{
	return single_open(file, so2_show, NULL);
}

static const struct proc_ops so2_ops = {
	.proc_open = so2_open,
	.proc_read = seq_read,
	.proc_lseek = seq_lseek,
	.proc_release = single_release,
	.proc_write = so2_write,
};

static int __init so2_init(void)
{
	if (!proc_create("so2_monitor", 0666, NULL, &so2_ops))
		return -ENOMEM;
	return 0;
}

static void __exit so2_exit(void)
{
	remove_proc_entry("so2_monitor", NULL);
}

module_init(so2_init);
module_exit(so2_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Laboratorio SO2 - USAC");
MODULE_DESCRIPTION("Interfaz /proc para metricas y umbral");
