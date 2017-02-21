#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>


#define THR_CNT 5
#define LISTEN_BACKLOG 50

int *queue;
int queuesz;
int qhead;
int qnumitems;
pthread_cond_t qcond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t qmut = PTHREAD_MUTEX_INITIALIZER;

void init_queue()
{
    queuesz = 10;
    queue = malloc(10);
    qhead = 0;
    qnumitems = 0;
}


int insert_q_back(int item)
{
    if(qnumitems >= queuesz) {
        return - 1;
    }
    int qend = (qhead + qnumitems) % queuesz;
    queue[qend] = item;
    qnumitems++;

    return 0;
}


int get_q_front()
{
    if(qnumitems == 0) {
        return - 1;
    }
    int oldhead = qhead;
    qnumitems--;
    qhead = (qhead + 1 ) % queuesz;
    return queue[oldhead];
}

void *(thrpool_loop) (void * arg)
{
    pthread_mutex_lock(&qmut);
    while(pthread_cond_wait(&qcond, &qmut) == 0)
    {
        int a = get_q_front();
        pthread_mutex_unlock(&qmut);
        printf("%lx: processing %d\n", pthread_self(), a);
    }
    return NULL;
}


#define handle_error(msg) \
   do { perror(msg); exit(EXIT_FAILURE); } while (0)

void *(listener) (void * arg)
{

    /*
    while(1) {
        pthread_mutex_lock(&qmut);
        int r = rand();
        printf("listener insert %d\n", r);
        int rc = insert_q_back(r);
        pthread_mutex_unlock(&qmut);
        if(rc == 0)
            pthread_cond_signal(&qcond);
        else
            printf("could not insert into queue\n");
        usleep(rand() % 10000);
    }
    */


    int sfd, cfd;
    struct sockaddr_un my_addr, peer_addr;
    socklen_t peer_addr_size;

    sfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sfd == -1)
        handle_error("socket");

    memset(&my_addr, 0, sizeof(struct sockaddr_un));
    /* Clear structure */
    my_addr.sun_family = AF_UNIX;
    strncpy(my_addr.sun_path, "/tmp/az.socket",
            sizeof(my_addr.sun_path) - 1);

    unlink(my_addr.sun_path);
    if (bind(sfd, (struct sockaddr *) &my_addr,
                sizeof(struct sockaddr_un)) == -1)
        handle_error("bind");

    if (listen(sfd, LISTEN_BACKLOG) == -1)
        handle_error("listen");

    /* Now we can accept incoming connections one
       at a time using accept(2) */

    peer_addr_size = sizeof(struct sockaddr_un);
    cfd = accept(sfd, (struct sockaddr *) &peer_addr,
            &peer_addr_size);

    char buf[256];
    int len = 256;
    //while(read(cfd, buf, len)) printf("buf=%s\n", buf);


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
