#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>

int main() {
    int fd[2], nb;
    pid_t cpid;
    char inf[] = "Welcome to LPU\n";
    char rbuff[50];
    pipe(fd);

    if((cpid=fork()) == -1) {
        printf("Parent failed to create the child process");
        exit(1);
    }
    
    if(cpid == 0) {
        close(fd[1]);
        nb=read(fd[0],rbuff,sizeof(rbuff));
        printf("The information recieved by the child from the pipe is: %s",rbuff);
        exit(0);
    } else {
        close(fd[0]);
        write(fd[1],inf,(strlen(inf)+ 1));
        printf("The information written by the Parent process in the pipe is: %s" ,inf);
    }
    
    return 0;
}