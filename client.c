#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>


#include <sys/types.h>
#include <netdb.h>


#define BUF_SIZE 500
#define THR_CNT 5
#define LISTEN_BACKLOG 50

#define DEBUG true
#ifdef DEBUG
#define out printf
#else
#define out
#endif


int *queue;
int queuesz;
int qhead;
int qnumitems;
pthread_cond_t qcond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t qmut = PTHREAD_MUTEX_INITIALIZER;
int server_up;

void client_loop ()
{

    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd == -1) {
        perror("client socket:");
        return NULL;
    }
    out("client socket ok\n");

    int port = 19002;
    struct sockaddr_in bindaddr = {0};
    bindaddr.sin_family = AF_INET;
    bindaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    bindaddr.sin_port = htons(port);

    int rc = connect(sfd, (struct sockaddr *)&bindaddr, sizeof(bindaddr));
    if (rc == -1) {
        perror("client bind: ");
        return NULL;
    }
    out("client bind ok\n");

    char *msg = "hello message, make longer message to see difference in timing";
    int len = strlen(msg) + 1;
    /* +1 for terminating null byte */

    if (len + 1 > BUF_SIZE) {
        fprintf(stderr, "Ignoring long message in argument\n");
        return NULL;
    }

    for(int ii = 0; ii < 100000; ii++) {
        if (write(sfd, msg, len) != len) {
            fprintf(stderr, "client partial/failed write\n");
            exit(EXIT_FAILURE);
        }

        char buf[128];
        int nread = read(sfd, buf, sizeof(buf));
        if (nread == -1) {
            perror("client reading");
            exit(EXIT_FAILURE);
        }
        out("Received %zd bytes: %s\n", nread, buf);
    }
    if (write(sfd, "exit", 5) != len) {
    }
    return NULL;
}


#define handle_error(msg) \
   do { perror(msg); exit(EXIT_FAILURE); } while (0)

void *(server_loop) (void * arg)
{
    server_up = 1;
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1) {
        perror("server socket:");
        return NULL;
    }
    out("server socket ok\n");

    int port = 7500;
    struct sockaddr_in bindaddr = {0};
    bindaddr.sin_family = AF_INET;
    bindaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    bindaddr.sin_port = htons(port);
    int rc = bind(listenfd, (struct sockaddr *)&bindaddr, sizeof(bindaddr));
    if (rc == -1) {
        perror("server bind: ");
        return NULL;
    }
    out("server bind ok\n");

    rc = listen(listenfd, SOMAXCONN);
    if (rc == -1) {
        perror("server listen: ");
        return NULL;
    }
    out("server listen ok\n");

    struct sockaddr_un client_addr;
    socklen_t clilen = sizeof(client_addr);

    int fd = accept(listenfd, (struct sockaddr *)&client_addr, &clilen);
    if (fd == -1) {
        perror("server accept:");
        exit(1);
    }

    while (1) {
        char buf[128];
        int listenfd = fd;

        ssize_t n = read(listenfd, buf, sizeof(buf));
        out("server read %s\n", buf);

        int len = write(listenfd, buf, n);
        if (len != n) {
            out("server partial/failed write\n");
        }

        if (strcmp(buf, "exit") == 0) break;
    }
    return NULL;
}


int main ()
{
    pthread_t client;
    pthread_t server;
    pthread_attr_t attr;
    int rc;

    int s = pthread_attr_init(&attr);
    if (s != 0)
        handle_error("pthread_attr_init");

    client_loop();
    return 0;
}
