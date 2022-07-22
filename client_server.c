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


#define BUF_SIZE 50000
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

void *(client_loop) (void * arg)
{
    while(!server_up) usleep(100000);
    out("server is up starting client\n");
    usleep(100000);

    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd == -1) {
        perror("client socket:");
        return NULL;
    }
    out("client socket ok\n");

    int port = 7500;
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

    char msg[BUF_SIZE] = "hello message";
    for(int i = sizeof("hello message") - 1; i < BUF_SIZE - 1; i++) {
        msg[i] = 'a' + rand() % 24;
    }
    int msglen = strlen(msg);
    msg[msglen++] = '\0';

    for(int ii = 0; ii < 100000; ii++) {
        if (write(sfd, msg, msglen) != msglen) {
            fprintf(stderr, "client partial/failed write\n");
            exit(EXIT_FAILURE);
        }

        char buf[BUF_SIZE];
        int nread = read(sfd, buf, sizeof(buf));
        if (nread == -1) {
            perror("client reading");
            exit(EXIT_FAILURE);
        }

        if (nread != msglen) { 
            out("bad number of bytes received: %d msglen: %d\n", nread, msglen);
        }
        if(memcmp(msg, buf, nread) != 0) {
            out("Bad content Received %d bytes: %s\n", nread, buf);
        }
        out("Client Received %d bytes: %.20s\n", nread, buf);
        sleep(1);
    }
    if (write(sfd, "quit", 5) != 5) {
            fprintf(stderr, "Fail to write\n");
            exit(EXIT_FAILURE);
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
        char buf[BUF_SIZE];
        int listenfd = fd;

        ssize_t n = read(listenfd, buf, sizeof(buf));
        out("server read len:%zd buf:'%.20s'; writing it all back to client\n", n, buf);

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

    rc = pthread_create(&server, &attr, server_loop, NULL );
    if (rc) abort();

    rc = pthread_create(&client, &attr, client_loop, NULL );
    if (rc) abort();

    rc = pthread_join(client, NULL);
    if (rc) abort();
    rc = pthread_join(server, NULL);
    if (rc) abort();
    return 0;
}
