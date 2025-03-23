#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

static int g_sfd;

static g_sfd;

struct socket_msg {
    unsigned int sdid;
};

struct socket_cmd {
    int cmd;
};

static int socket_init(void)
{
    struct sockaddr_in addr;
    struct socket_msg msg;
    char recvBuff[1024] = {0};
    int sfd, conn_fd;
    uint32_t sdid;
    int ret;

    sfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&addr, '0', sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(5000); 

    ret = bind(sfd, (struct sockaddr*)&addr, sizeof(struct sockaddr_in));
    if (ret != 0) {
        printf("bind fail. (ret=%d)\n", ret);
        return ret;
    }
    listen(sfd, 10);
    conn_fd = accept(sfd, (struct sockaddr*)NULL, NULL); 
    if (conn_fd < 0) {
        printf("accept fail. (conn_fd=%d)\n", conn_fd);
        return -1;
    }
    ret = recv(conn_fd, &msg, sizeof(struct socket_msg), 0);
    printf("recv. ret=%d\n", ret);
    printf("recvBuff=%s\n", recvBuff);

    printf("sdid=%u\n", msg.sdid);

    return 0;
}

int main(int argc, char *argv[])
{
    int ret, sfd;

    ret = socket_init();
    if (ret != 0) {
        printf("socket init fail. (ret=%d)\n", ret);
        return ret;
    }

    return 0;
}
