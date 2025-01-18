#ifndef MYLOG_H
#define MYLOG_H

#include <linux/printk.h>
#include <linux/sched.h>

#define log_info(fmt, args...) do {                                         \
    printk(KERN_INFO "[%d][%d][%s][%d]" fmt,                                \
        current->tgid, current->pid, __FUNCTION__, __LINE__, ## args);      \
} while(0) 

#endif
