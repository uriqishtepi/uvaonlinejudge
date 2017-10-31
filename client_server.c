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
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int sfd, s;
    size_t len;
    ssize_t nread;
    char buf[BUF_SIZE];

    const char *port = "7500";

    /* Obtain address(es) matching host/port */

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
    hints.ai_flags = 0;
    hints.ai_protocol = 0;          /* Any protocol */
    char *lochost = "localhost";

    s = getaddrinfo(lochost, port, &hints, &result);
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }

    for (rp = result; rp != NULL; rp = rp->ai_next) {
        sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sfd == -1)
            continue;

        if (connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1)
            break;                  /* Success */

printf("AZ: connect failed sfd %d\n", sfd);
        close(sfd);
    }
printf("AZ: sfd %d\n", sfd);

    if (rp == NULL) {               /* No address succeeded */
        fprintf(stderr, "Could not connect\n");
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(result);           /* No longer needed */

    /* Send remaining command-line arguments as separate
       datagrams, and read responses from server */

    char *msg = "hello";
    len = strlen(msg) + 1;
    /* +1 for terminating null byte */

    if (len + 1 > BUF_SIZE) {
        fprintf(stderr, "Ignoring long message in argument\n");
        return NULL;
    }

    if (write(sfd, msg, len) != len) {
        fprintf(stderr, "partial/failed write\n");
        exit(EXIT_FAILURE);
    }

    nread = read(sfd, buf, BUF_SIZE);
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
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int sfd, s;
    struct sockaddr_storage peer_addr;
    socklen_t peer_addr_len;
    ssize_t nread;
    char buf[BUF_SIZE];

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
    hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
    hints.ai_protocol = 0;          /* Any protocol */
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;
    const char *port = "7500";

    s = getaddrinfo(NULL, port, &hints, &result);
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }
    for (rp = result; rp != NULL; rp = rp->ai_next) {
        sfd = socket(rp->ai_family, rp->ai_socktype,
                rp->ai_protocol);
        printf("server trying socket fam %d, type %d, prot %d\n", rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sfd == -1)
            continue;

        if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
            break;                  /* Success */

printf("AZ: bind failed sfd %d\n", sfd);
        close(sfd);
    }
printf("AZ: sfd %d\n", sfd);

    if (rp == NULL) {               /* No address succeeded */
        fprintf(stderr, "Server could not bind\n");
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(result);           /* No longer needed */


    /* Read datagrams and echo them back to sender */

    fprintf(stderr, "Server binding\n");
    for (;;) {
        peer_addr_len = sizeof(struct sockaddr_storage);
        nread = recvfrom(sfd, buf, BUF_SIZE, 0,
                (struct sockaddr *) &peer_addr, &peer_addr_len);
printf("AZ: server nread %d\n", nread);
        if (nread == -1)
            continue;               /* Ignore failed request */

        char host[NI_MAXHOST], service[NI_MAXSERV];

        s = getnameinfo((struct sockaddr *) &peer_addr,
                peer_addr_len, host, NI_MAXHOST,
                service, NI_MAXSERV, NI_NUMERICSERV);
        if (s == 0)
            printf("Received %zd bytes from %s:%s\n",
                    nread, host, service);
        else
            fprintf(stderr, "getnameinfo: %s\n", gai_strerror(s));

        if (sendto(sfd, buf, nread, 0,
                    (struct sockaddr *) &peer_addr,
                    peer_addr_len) != nread)
            fprintf(stderr, "Error sending response\n");
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
