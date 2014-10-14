#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>


#define FORL(ii,s,e) for(int ii = s; ii < e; ii++)

/* Example of two processes communicatting via a pipe
 */


int main()
{
    //call 10 threads to increase variable passed in

    int pipefd[2]; //one for in the other for out
    int rc = pipe2(pipefd, O_NONBLOCK);
    if(-1 == rc) {
        perror("Opening pipe\n");
        exit(1);
    }

    pid_t pid = fork();
    if(-1 == pid) {
        perror("Opening pipe\n");
        exit(1);
    }

    //writes on fd 1, reads on 0
    if(0 == pid) { //child process writes on fd 1
        printf("Child process\n");
        const char * str = "Child sending this";
        rc = write(pipefd[1], str, strlen(str));
        if(-1 == rc) {
            perror("Write Error");
        }

        char ch;
        while((rc = read(pipefd[0], &ch, 1)) > 0)
            write(STDOUT_FILENO, &ch, 1);

        close(pipefd[0]);
        close(pipefd[1]);
        exit(1);
    }
    else { //parent writes on fd 1
        printf("Parent process\n");

        const char * str = "Parent sending this";
        rc = write(pipefd[1], str, strlen(str));
        if(-1 == rc) {
            perror("Write Error");
        }

        char ch;
        while((rc = read(pipefd[0], &ch, 1)) > 0)
            write(STDOUT_FILENO, &ch, 1);

        close(pipefd[0]);
        close(pipefd[1]);
        wait(NULL);
        exit(1);
    }

    return 0;
}

