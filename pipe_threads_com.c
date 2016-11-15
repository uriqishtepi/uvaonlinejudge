#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <pthread.h>


struct readwritepipe {
    int pipefd_w;
    int done;
};


void * childFunc(void * arg)
{
    struct readwritepipe * rwp = (struct readwritepipe*) arg;
    int fd = rwp->pipefd_w;

    for (int i = 0; i < 10; i++) {
        const char str[256];
        snprintf(str, sizeof(str), "Child sending this, i=%d\n", i);

        int rc = write(fd, str, strlen(str));
        if(-1 == rc) {
            perror("Write Error");
        }
    }
    rwp->done = 1;
}

/* Example of two threads child/parent communicatting via a pipe
 */
int main()
{
    int pipefd[2]; //[0] for IN (read) [1] for OUT (write)
    int rc = pipe2(pipefd, O_NONBLOCK);
    if(-1 == rc) {
        perror("Opening pipe\n");
        exit(1);
    }

    pthread_t thv;
    struct readwritepipe rwp;
    rwp.pipefd_w = pipefd[1];
    rwp.done = 0;

    //writes done on spawned thread on fd 1, reads done on 0
    pthread_create(&thv, NULL, childFunc, &rwp);

    char ch;
    while(!rwp.done) { //parent reads on fd 0
        while((rc = read(pipefd[0], &ch, 1)) > 0)
            write(STDOUT_FILENO, &ch, 1);
        usleep(100);
    }

    while((rc = read(pipefd[0], &ch, 1)) > 0)
        write(STDOUT_FILENO, &ch, 1);

    printf("Parent process done\n");
    pthread_join(thv, NULL);

    close(pipefd[0]);
    close(pipefd[1]);

    return 0;
}
