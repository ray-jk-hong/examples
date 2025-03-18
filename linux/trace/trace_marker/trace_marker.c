#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>

#define TRACE_MARKER_PATH "/sys/kernel/debug/tracing/trace_marker"
#define TRACE_ON_PATH "/sys/kernel/debug/tracing/tracing_on"

static int trace_fd = -1;

static void trace_write(const char *fmt, ...)
{
    va_list ap;
    char buf[256];
    int n;
    
    if (trace_fd < 0) {
        printf("trace open fail\n");
        return;
    }
    va_start(ap, fmt);
    n = vsnprintf(buf, 256, fmt, ap);
    va_end(ap);
    
    write(trace_fd, buf, n);    
}

static int trace_open(void)
{
    trace_fd = open(TRACE_MARKER_PATH, O_WRONLY);
    if (trace_fd < 0) {
        printf("trace open fail\n");
        return -1;
    }


    return 0;
}

static void trace_close(void)
{
    if (trace_fd >= 0) {
        close(trace_fd);
        trace_fd = -1;
    }
}

static void trace_on(void)
{
    int fd = open(TRACE_ON_PATH, O_WRONLY);
    char *buf = "1";
    if (fd > 0) {
        write(fd, buf, strlen(buf));
        close(fd);
    }
}

static void trace_off(void)
{
    int fd = open(TRACE_ON_PATH, O_WRONLY);
    char *buf = "0";
    if (fd > 0) {
        write(fd, buf, strlen(buf));
        close(fd);
    }
}

int main(int argc, char *argv[])
{
    int ret, i;

    trace_on();
    ret = trace_open();
    if (ret < 0) {
        printf("trace open fail\n");
        return ret;
    }
    for (i = 0; i < 10; i++) {
        trace_write(" [%s] trace cnt = %d\n", __func__, i);
        usleep(500 * 1000);
    }
    trace_close();
    trace_off();
    return 0;
}
