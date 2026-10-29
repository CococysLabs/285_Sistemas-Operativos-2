#include <linux/module.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/pid.h>
#include <linux/mm.h>
#include <linux/cred.h>

static int pid = 1;
module_param(pid, int, 0444);

static int __init pcb_init(void)
{
    struct task_struct *t;
    rcu_read_lock();
    t = pid_task(find_vpid(pid), PIDTYPE_PID);
    
    if (!t) {
        rcu_read_unlock();
        pr_err("pcbinfo: PID %d no existe\n", pid);
        return -ESRCH;
    }
    
    pr_info("pcbinfo: comm=%s pid=%d tgid=%d ppid=%d\n",
            t->comm, t->pid, t->tgid,
            task_pid_nr(rcu_dereference(t->real_parent)));
            
    pr_info("pcbinfo: estado=%c uid=%u\n",
            task_state_to_char(t),
            from_kuid(&init_user_ns, task_uid(t)));
            
    if (t->mm)
        pr_info("pcbinfo: rss=%lu KB\n",
                get_mm_rss(t->mm) << (PAGE_SHIFT - 10));
                
    rcu_read_unlock();
    return 0;
}

static void __exit pcb_exit(void) { }

module_init(pcb_init);
module_exit(pcb_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sopes 2");
MODULE_DESCRIPTION("Módulo del kernel para mostrar información del PCB de un proceso dado su PID");