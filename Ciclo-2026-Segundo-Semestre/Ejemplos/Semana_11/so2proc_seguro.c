#include <linux/capability.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>

static DEFINE_MUTEX(cfg_lock);
static int umbral;

static int seguro_show(struct seq_file *m, void *v)
{
	int actual;
	(void)v;
	mutex_lock(&cfg_lock);
	actual = umbral;
	mutex_unlock(&cfg_lock);
	seq_printf(m, "{\"umbral_mb\":%d}\n", actual);
	return 0;
}

static ssize_t seguro_write(struct file *file, const char __user *user_buf,
			    size_t len, loff_t *offset)
{
	char buf[16];
	int value;

	(void)file;
	(void)offset;
	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;
	if (len == 0 || len >= sizeof(buf))
		return -EINVAL;
	if (copy_from_user(buf, user_buf, len))
		return -EFAULT;
	buf[len] = '\0';
	if (kstrtoint(strim(buf), 10, &value) || value < 0 || value > 65536)
		return -EINVAL;
	mutex_lock(&cfg_lock);
	umbral = value;
	mutex_unlock(&cfg_lock);
	return len;
}

static int seguro_open(struct inode *inode, struct file *file)
{
	return single_open(file, seguro_show, NULL);
}

static const struct proc_ops seguro_ops = {
	.proc_open = seguro_open,
	.proc_read = seq_read,
	.proc_lseek = seq_lseek,
	.proc_release = single_release,
	.proc_write = seguro_write,
};

static int __init seguro_init(void)
{
	if (!proc_create("so2_monitor", 0644, NULL, &seguro_ops))
		return -ENOMEM;
	return 0;
}

static void __exit seguro_exit(void)
{
	remove_proc_entry("so2_monitor", NULL);
}

module_init(seguro_init);
module_exit(seguro_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Laboratorio SO2 - USAC");
MODULE_DESCRIPTION("Interfaz /proc con validacion y control de capacidad");
