/* Example client and server in one file:
 *   Spawns N client threads to connect to one server thread.
 *   Server thread spawns client_service thread for each client connection.
 *   Once connection is established, client sends a large message,
 *   server thread receives it and sends it back and client thread verifies
 *   that it is the same message that it sent initially.
 */
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>
#include <assert.h>

#include <sys/types.h>
#include <netdb.h>


#define BUF_SIZE 50000
#define THR_CNT 5
#define LISTEN_BACKLOG 50
#define MAX_THREADS 10

#define DEBUG true
#ifdef DEBUG
#define out printf
#else
#define out
#endif

#define handle_error(msg) \
   do { perror(msg); exit(EXIT_FAILURE); } while (0)

int server_up;

void *(client_loop) (void * arg)
{
    int cl_id = (int) arg;
    while(!server_up) usleep(100000);
    out("server is up starting client\n");
    usleep(100000);

    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd == -1) {
        perror("client socket:");
        return NULL;
    }
    out("client %d socket ok\n", cl_id);

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
    out("client %d bind ok\n", cl_id);

    char msg[BUF_SIZE];
    int len = sprintf(msg, "hello from %d ", cl_id);

    // first message just sends the client id
    if (write(sfd, msg, len + 1) != len + 1) {
        fprintf(stderr, "client partial/failed write\n");
        exit(EXIT_FAILURE);
    }

    for(int i = len; i < BUF_SIZE - 1; i++) {
        msg[i] = 'a' + rand() % 24;
    }
    int msglen = strlen(msg);
    msg[msglen++] = '\0';

    for(int ii = 0; ii < 100000; ii++) {
        // send size of bytes in the msg
        int netbyte = htonl(msglen);
        if (write(sfd, &netbyte, sizeof(int)) != sizeof(int)) {
            fprintf(stderr, "client partial/failed write of header\n");
            exit(EXIT_FAILURE);
        }
        if (write(sfd, msg, msglen) != msglen) {
            fprintf(stderr, "client partial/failed write\n");
            exit(EXIT_FAILURE);
        }

        // now read from the server -- should be identical msg
        int srv_msglen = 0;
        ssize_t hdrsz = read(sfd, &srv_msglen, sizeof(int));
        assert(hdrsz == sizeof(int));
        srv_msglen = ntohl(srv_msglen);
        if (srv_msglen != msglen) { 
            out("Client %d: bad number of bytes in header received: %d msglen: %d\n", cl_id, srv_msglen, msglen);
        }

        char buf[BUF_SIZE];
        int nread = 0;
        while(nread < srv_msglen) {
            int n = read(sfd, buf + nread, sizeof(buf));
            if (n != srv_msglen) out("client %d partial read from server len:%zd buf:'%.20s'\n", cl_id, n, buf + nread);
            if (n == -1) {
                perror("client reading");
                exit(EXIT_FAILURE);
            }

            nread += n;
        }
        if (nread != msglen) { 
            out("Client %d: bad number of bytes received: %d msglen: %d\n", cl_id, nread, msglen);
        }
        if(memcmp(msg, buf, nread) != 0) {
            out("Client %d: Bad content Received %d bytes: %s\n", cl_id, nread, buf);
        }
        out("Client %d Received %d bytes: %.20s\n", cl_id, nread, buf);
        usleep(500000 + rand() % 1000000);
    }
    if (write(sfd, "quit", 5) != 5) {
            fprintf(stderr, "Fail to write\n");
            exit(EXIT_FAILURE);
    }
    return NULL;
}

/* server servicing client routine running in separate thread */
void *(service_client) (void *arg)
{
    char buf[BUF_SIZE];
    int listenfd = (int)arg;
    ssize_t hello_len = read(listenfd, buf, sizeof(buf));
    assert(hello_len > 0);
    int cl_id = atoi(buf + sizeof("hello from"));
    out("Service Client %d on fd %d\n", cl_id, listenfd);
    assert (cl_id > 0 && cl_id <= MAX_THREADS);

    while (1) {

        int msglen;
        ssize_t hdrsz = read(listenfd, &msglen, sizeof(int));
        assert(hdrsz == sizeof(int));
        msglen = ntohl(msglen);

        int nread = 0;
        while (nread < msglen) {
            int n = read(listenfd, buf + nread, msglen);
            if (n == -1) {
                perror("client reading");
                exit(EXIT_FAILURE);
            }

            if (n != msglen) {
                out("server fd %d partial read from cl_id %d len:%zd buf:'%.20s'\n", listenfd, cl_id, n, buf + nread);
            }
            nread += n;
        }

        out("server fd %d read from cl_id %d len:%zd buf:'%.20s'; writing it all back to client\n", listenfd, cl_id, nread, buf);

        int netbyte = htonl(nread);
        if (write(listenfd, &netbyte, sizeof(int)) != sizeof(int)) {
            fprintf(stderr, "server partial/failed write of header\n");
            exit(EXIT_FAILURE);
        }

        int len = write(listenfd, buf, nread);
        if (len != nread) {
            out("server fd=%d clid=%d partial/failed write\n", listenfd, cl_id);
        }

        if (strcmp(buf, "exit") == 0) break;
    }
    return NULL;
}

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

    while (1) {
        struct sockaddr_un client_addr;
        socklen_t clilen = sizeof(client_addr);
        int fd = accept(listenfd, (struct sockaddr *)&client_addr, &clilen);
        if (fd == -1) {
            perror("server accept:");
            exit(1);
        }

        int on = 1;
        int len = sizeof(on);
        int rc = setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, (char *)&on, len);
        if (rc != 0) {
            out("%s: Couldnt turn on keep alive on fd %d: %d %s\n", __func__, fd, errno, strerror(errno));
            close(fd);
            exit(1);
        }

        struct linger linger_data = {.l_onoff = 0, .l_linger = 1};
        len = sizeof(linger_data);
        rc = setsockopt(fd, SOL_SOCKET, SO_LINGER, (char *)&on, len);
        if (rc != 0) {
            out("%s: Couldnt turn off linger on fd %d: %d %s\n", __func__, fd, errno, strerror(errno));
            close(fd);
            exit(1);
        }

        pthread_t tid;
        pthread_attr_t attr;
        rc = pthread_create(&tid, &attr, service_client, (void *)fd);
        if (rc) abort();
    }

    return NULL;
}

int main ()
{
    pthread_t client[10];
    pthread_t server;
    pthread_attr_t attr;
    int rc;

    int s = pthread_attr_init(&attr);
    if (s != 0)
        handle_error("pthread_attr_init");

    rc = pthread_create(&server, &attr, server_loop, NULL);
    if (rc) abort();

    for(int i = 0; i < MAX_THREADS; i++) {
        rc = pthread_create(&client[i], &attr, client_loop, (void *) i + 1);
        if (rc) abort();
    }

    for(int i = 0; i < 10; i++) {
        rc = pthread_join(client[i], NULL);
        if (rc) abort();
    }

    rc = pthread_join(server, NULL);
    if (rc) abort();
    return 0;
}
