#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

struct socket_msg {
    unsigned int sdid;
};

static int client_init()
{
    struct sockaddr_in addr;
    int cfd, conn_fd, ret;
    struct socket_msg msg;
    char sendBuff[1025];


    cfd = socket(AF_INET, SOCK_STREAM, 0);
    if (cfd < 0) {
        printf("Socket creat fail. (cfd=%d\n)", cfd);
        return -1;
    }
    memset(&addr, '0', sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5000); 

    if (inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr) <= 0) {
        printf("\n inet_pton error occured\n");
        return 1;
    }

    conn_fd = connect(cfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
    if (conn_fd < 0) {
        printf("Connet fail. (conn_fd=%d)\n", conn_fd);
        return -1;
    }
    
    msg.sdid = 100;
    ret = send(conn_fd, &msg, sizeof(msg), 0);
    /* ret = write(conn_fd, &msg, sizeof(msg)); */
    /* snprintf(sendBuff, sizeof(sendBuff), "%s\n", "HelloWorld") */
    /* ret = write(conn_fd, sendBuff, strlen(sendBuff) - 1); */
    if (ret < 0) {
        printf("Send fail. (ret=%d)\n", ret);
        return -1;
    }


    return 0;
}

int main(int argc, char *argv[])
{
    int ret;

    ret = client_init();
    if (ret != 0) {
        printf("Client init. (ret=%d)\n", ret);
        return ret;
    }

    return 0;
}
