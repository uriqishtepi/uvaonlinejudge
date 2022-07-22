/* threadpool example to connect via network and send a msg to process
 * connect via 'echo "blah" | nc 0.0.0.0 7500' or telnet.
 * Example uses a queue to save and retrieve work to be performed,
 */
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <pthread.h>

#define THR_CNT 5
#define LISTEN_BACKLOG 50
#define QSIZE 50

char **queue;
int queuesz;
int qhead;
int qnumitems;
pthread_cond_t qcond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t qmut = PTHREAD_MUTEX_INITIALIZER;

void init_queue()
{
    queuesz = QSIZE;
    queue = malloc(queuesz * sizeof(char *));
    qhead = 0;
    qnumitems = 0;
}


// insert to queue back
// call with mutex held
int enqueue(char *item, size_t cnt)
{
    if(qnumitems >= queuesz) {
        return - 1;
    }
    int qend = (qhead + qnumitems) % queuesz;
    char *itemcpy = malloc(cnt);
    memcpy(itemcpy, item, cnt);
    queue[qend] = itemcpy;
    qnumitems++;

    return 0;
}

// return the front element if there is one
// caller takes ownership and needs to eventually free the element returned
// call with mutex held
char *dequeue()
{
    if(qnumitems == 0) {
        return NULL;
    }
    int oldhead = qhead;
    qnumitems--;
    qhead = (qhead + 1 ) % queuesz;
    return queue[oldhead];
}

void *(thrpool_loop) (void * arg)
{
    int done = 0;
    while(!done)
    {
        pthread_mutex_lock(&qmut);
        int rc = pthread_cond_wait(&qcond, &qmut);
        assert(rc == 0 && "Error with cont wait");
        char *item = dequeue();
        pthread_mutex_unlock(&qmut);
        if (item == NULL)
            continue;
        printf("%lx: processing %s\n", pthread_self(), item);
        free(item);
    }
    return NULL;
}


#define handle_error(msg) \
   do { perror(msg); exit(EXIT_FAILURE); } while (0)

void *(listener) (void * arg)
{
    printf("listener starting, getting a socket\n");
    int tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (tcp_socket == -1)
        handle_error("socket");

    int port = 7500;
    struct sockaddr_in bindaddr = {0};
    bindaddr.sin_family = AF_INET;
    bindaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    bindaddr.sin_port = htons(port);

    printf("binding\n");
    struct sockaddr_un peer_addr;
    socklen_t peer_addr_size = sizeof(struct sockaddr_un);
    if (bind(tcp_socket, (struct sockaddr *) &bindaddr, sizeof(struct sockaddr_un)) == -1)
        handle_error("bind");

    if (listen(tcp_socket, LISTEN_BACKLOG) == -1)
        handle_error("listen");

    // Accept incoming connections one at a time
    while (1) {
        printf("accepting\n");
        int fd = accept(tcp_socket, (struct sockaddr *) &peer_addr, &peer_addr_size);
        if (fd == -1) {
            handle_error("server accept");
        }

        printf("reading\n");
        char buf[256];
        int len = 256;
        int rd;
        while((rd = read(fd, buf, len))) {
            if (strcmp(buf, "exit") == 0) {
                printf("Exiting...\n");
                exit(1);
            }
            write(fd, "0", 1);
            printf("listener insert in q buf:");
            for(int i=0;i<rd;i++){
                printf("%x.", buf[i]);
            }
            printf("\n");

            pthread_mutex_lock(&qmut);
            int rc = enqueue(buf, rd);
            pthread_mutex_unlock(&qmut);

            if(rc == 0)
                pthread_cond_signal(&qcond);
            else
                printf("could not insert into queue, dropping msg\n");
        }
    }
    return NULL;
}


int main ()
{
    pthread_t thid[THR_CNT];
    pthread_t list;
    pthread_attr_t attr;
    init_queue();
    int rc;

    int s = pthread_attr_init(&attr);
    if (s != 0)
        handle_error("pthread_attr_init");

    for(int i = 0; i < THR_CNT; i++) {
        rc = pthread_create(&thid[i], &attr, thrpool_loop, NULL );
        if (rc) abort();
    }

    rc = pthread_create(&list, &attr, listener, NULL );
    if (rc) abort();

    for(int i = 0; i < THR_CNT; i++) {
        rc = pthread_join(thid[i], NULL );
        if (rc) abort();
    }

    return 0;
}
