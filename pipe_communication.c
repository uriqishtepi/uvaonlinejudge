#include <pthread.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>


#define FORL(ii,s,e) for(int ii = s; ii < e; ii++)

/* Example of two processes child/parent communicatting via a pipe
 */
int parent_child()
{
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



/* example where we exec a different command and we pipe it's output
 * back to this program */
int main()
{
    int pipefd[2];

    int rc = pipe2(pipefd, O_NONBLOCK);
    if(-1 == rc) {
        perror("Opening pipe\n");
        exit(1);
    }
    int pid;

    if((pid=fork()) == -1) {
        perror("Opening pipe\n");
        exit(1);
    }
    else if(0 == pid) { //child
        while( dup2(pipefd[1], STDOUT_FILENO) == -1 && (errno == EINTR)) {}
        const char * cmd = "/bin/ls";
        const char * arg = "/tmp/";
        close(pipefd[1]);
        close(pipefd[0]);
        execl(cmd, cmd, arg);
        perror("execl"); //if we get here is error
        exit(1);
    }
    //parent

    close(pipefd[1]); //not going to write

    char buffer[4096];
    while (1) {
        ssize_t count = read(pipefd[0], buffer, sizeof(buffer));
        if (count == -1) {
            continue;
/*
            if (errno == EINTR) {
                continue;
            } else {
                perror("read");
                exit(1);
            }
*/
        } else if (count == 0) {
            break;
        } else {
            write(STDERR_FILENO, buffer, count);
        }
    }

    close(pipefd[0]);
    wait(0);
    return 0;
}
