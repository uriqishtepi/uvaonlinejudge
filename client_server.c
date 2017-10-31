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

int *queue;
int queuesz;
int qhead;
int qnumitems;
pthread_cond_t qcond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t qmut = PTHREAD_MUTEX_INITIALIZER;

void *(client_loop) (void * arg)
{
    sleep(1);
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd == -1) {
        perror("client socket:");
        return NULL;
    }
    fprintf(stderr, "client socket ok\n");

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
    fprintf(stderr, "client bind ok\n");

    char *msg = "hello";
    int len = strlen(msg) + 1;
    /* +1 for terminating null byte */

    if (len + 1 > BUF_SIZE) {
        fprintf(stderr, "Ignoring long message in argument\n");
        return NULL;
    }

    if (write(sfd, msg, len) != len) {
        fprintf(stderr, "partial/failed write\n");
        exit(EXIT_FAILURE);
    }

    char buf[128];
    int nread = read(sfd, buf, sizeof(buf));
printf("AZ: client nread %d\n", nread);
    if (nread == -1) {
        perror("client reading");
        //exit(EXIT_FAILURE);
    }
    else 
        printf("Received %zd bytes: %s\n", nread, buf);
    return NULL;
}


#define handle_error(msg) \
   do { perror(msg); exit(EXIT_FAILURE); } while (0)

void *(server_loop) (void * arg)
{
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1) {
        perror("server socket:");
        return NULL;
    }
    fprintf(stderr, "server socket ok\n");

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
    fprintf(stderr, "server bind ok\n");

    rc = listen(listenfd, SOMAXCONN);
    if (rc == -1) {
        perror("server listen: ");
        return NULL;
    }
    fprintf(stderr, "server listen ok\n");

    while (1) {
        struct sockaddr_un client_addr;
        socklen_t clilen = sizeof(client_addr);

        int fd = accept(listenfd, (struct sockaddr *)&client_addr, &clilen);
        if (fd == -1) {
            perror("server accept:");
            exit(1);
        }
        char buf[128];
        int listenfd = fd;
        fprintf(stderr, "server read\n");
        ssize_t n = read(listenfd, buf, sizeof(buf));
        fprintf(stderr, "server read %s\n", buf);

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

    rc = pthread_create(&client, &attr, client_loop, NULL );
    if (rc) abort();

    rc = pthread_create(&server, &attr, server_loop, NULL );
    if (rc) abort();

    rc = pthread_join(client, NULL);
    if (rc) abort();
    rc = pthread_join(server, NULL);
    if (rc) abort();
    return 0;
}
