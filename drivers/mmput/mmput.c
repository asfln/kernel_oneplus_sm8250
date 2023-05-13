#include <linux/module.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <linux/mm_types.h>
MODULE_LICENSE("GPL");

static int __init mmput_init(void)
{
    printk("into mmput_init.\n");
    struct pid * kpid=find_get_pid(current->pid);         //获取当前进程的描述符信息
    struct task_struct * task=pid_task(kpid, PIDTYPE_PID); //获取新进程的任务描述符信息
    struct mm_struct * mm_task=get_task_mm(task);         //获取进程对应任务的内存信息

    /*显示字段mm_users和字段mm_count的值*/
    printk("the mm_users of the mm_struct is:%d\n", mm_task->mm_users);
    printk("the mm_count of the mm_struct is:%d\n", mm_task->mm_count);

    /*显示与此mm_struct相关进程的父进程的TGID和PID*/
    printk("the tgid of the mm_strcut is:%d\n", mm_task->owner->tgid);
    printk("the pid of the mm_struct is:%d\n", mm_task->owner->pid);
    mmput(mm_task);            //调用函数mmput( )释放进程的内存空间
    printk("the new value of the mm_struct after the function mmput:\n");

    /*显示函数mmput( )调用之后的进程对应内存空间部分字段的值*/
    printk("the mm_users of the mm_struct is:%d\n", mm_task->mm_users);
    printk("the mm_count of the mm_struct is:%d\n", mm_task->mm_count);
    printk("the tgid of the mm_strcut is:%d\n", mm_task->owner->tgid);
    printk("the pid of the mm_struct is:%d\n", mm_task->owner->pid);
    printk("the current PID is:%d\n", current->pid);       //显示当前进程的PID值
    printk("out mmput_init.\n");
    return 0;
}

static void __exit mmput_exit(void)
{
    printk("Goodbye mmput\n");
}

module_init(mmput_init);
module_exit(mmput_exit);
