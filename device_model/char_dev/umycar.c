#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define DEV_PATH "/dev/my_dev"

int main(int argc, char *argv[])
{
    int fd = -1;
    char buf[50];

    fd = open(DEV_PATH, O_RDWR);
    if (fd < 0) {
        printf("Open fail. (%s, %d)\n", strerror(errno), errno);
        return -1;
    }
    write(fd, buf, 50);
    read(fd, buf, 50);
    lseek(fd, 10, SEEK_SET);
    lseek(fd, 20, SEEK_CUR);
    lseek(fd, 30, SEEK_END);
    write(fd, buf, 50);
    read(fd, buf, 50);

    return 0;
}

