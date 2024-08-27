#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdarg.h>

#define TRACE_PATH "/sys/kernel/debug/tracing/trace_marker"
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
    trace_fd = open(TRACE_PATH, O_WRONLY);
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

int main(int argc, char *argv[])
{
    int ret, i;

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

    return 0;
}
