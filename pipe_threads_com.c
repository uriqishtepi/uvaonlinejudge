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
    pthread_cond_t can_read;
    pthread_mutex_t mutex;
};


void * childFunc(void * arg)
{
    struct readwritepipe * rwp = (struct readwritepipe*) arg;
    int fd = rwp->pipefd_w;

    printf("Child process writing on %d\n", fd);
    const char * str = "Child sending this";
    int rc = write(fd, str, strlen(str));
    if(-1 == rc) {
        perror("Write Error");
    }
    rwp->done = 1;
}

#define FORL(ii,s,e) for(int ii = s; ii < e; ii++)


/* Example of two processes child/parent communicatting via a pipe
 */
int main()
{
    int pipefd[2]; //one for in the other for out
    int rc = pipe2(pipefd, O_NONBLOCK);
    if(-1 == rc) {
        perror("Opening pipe\n");
        exit(1);
    }

    pthread_t thv;
    struct readwritepipe rwp;
    //pthread_mutex_init(&rwp.mutex, NULL);
    //pthread_cond_init(&rwp.can_read, NULL);
    rwp.pipefd_w = pipefd[1];
    rwp.done = 0;

    //writes occure on fd 1, reads on 0
    printf("Child process thould be writing on %d\n", pipefd[1]);
    pthread_create(&thv, NULL, childFunc, &rwp); //so child will write on fd 1
    sleep(1);


    //pthread_mutex_lock(&rwp->mutex);
    while(!rwp.done) { //parent reads on fd 0
        //int rc = 0;
        //while(!rwp->done && rc == 0) 
        //    rc = pthread_cond_wait(&rwp->can_read, &rwp->mutex);

        usleep(100);
        char ch;
        while((rc = read(pipefd[0], &ch, 1)) > 0)
            write(STDOUT_FILENO, &ch, 1);
        
        //pthread_mutex_unlock(&rwp->mutex);
    }

    printf("Parent process done\n");
    pthread_join(thv, NULL);

    close(pipefd[0]);
    close(pipefd[1]);

    return 0;
}

