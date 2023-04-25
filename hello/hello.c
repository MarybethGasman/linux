#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/sched.h>

void print_all_processes(void) {
    struct task_struct *task;

    printk(KERN_INFO "Printing all processes:\n");

    for_each_process(task) {
        printk(KERN_INFO "PID: %d, Command: %s\n", task->pid, task->comm);
    }
}

void print_process_info(long pid) {
    struct task_struct *task;
    // struct mm_struct *mm;
    // struct files_struct *files;
    // int i;

    task = find_task_by_vpid(pid);
    if (task == NULL) {
        printk(KERN_INFO "Process with PID %ld does not exist\n", pid);
    } else {
        // Print memory space information
        printk(KERN_INFO "Task Memory Space:\n");
        printk(KERN_INFO "Start code: 0x%lx\n", task->mm->start_code);
        printk(KERN_INFO "End code: 0x%lx\n", task->mm->end_code);
        printk(KERN_INFO "Start data: 0x%lx\n", task->mm->start_data);
        printk(KERN_INFO "End data: 0x%lx\n", task->mm->end_data);
        printk(KERN_INFO "Start brk: 0x%lx\n", task->mm->start_brk);
        printk(KERN_INFO "Brk: 0x%lx\n", task->mm->brk);
        printk(KERN_INFO "Start stack: 0x%lx\n", task->mm->start_stack);
        printk(KERN_INFO "Current stack: 0x%lx\n", task->mm->stack_vm);

        // Print scheduling information
        printk(KERN_INFO "Task Scheduling Information:\n");
        printk(KERN_INFO "Priority: %d\n", task->prio);
        printk(KERN_INFO "Nice value: %d\n", task_nice(task));
        printk(KERN_INFO "Processor: %d\n", task_cpu(task));
    }
}
SYSCALL_DEFINE0(hello) {
    struct pt_regs *regs = current_pt_regs();
    long arg1 = regs->di;
    long arg2 = regs->si;
    long arg3 = regs->dx;

    printk(KERN_INFO "my_syscall called with args: %ld, %ld, %ld\n", arg1, arg2, arg3);
    print_process_info(arg1);
    return 0;
}

