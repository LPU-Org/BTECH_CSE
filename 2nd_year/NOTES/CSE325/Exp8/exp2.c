#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>

int main() {
    int fd1[2],fd2[2],nb;
    pid_t cpid;
    char inf1[] = "Welcome to LPU";
    char inf2[] = "Thank you";
    char buff[100];
    pipe(fd1);
    pipe(fd2);

    if(( cpid=fork())==-1) {
        printf("Parent failed to create the child process");
        exit(1);
    }

    if(cpid == 0) {
        close(fd1[0]);
        close(fd2[1]);
        write(fd1[1],inf1,strlen(inf1)+1);
        nb = read(fd2[0],buff,sizeof(buff));
        printf("The information received by the Child process is: %s\n",buff) ;
        exit(0);
    } else {
        close(fd1[1]);
        close(fd2[0]);
        write(fd2[1],inf2,strlen(inf2)+ 1 );
        nb= read(fd1[0],buff,sizeof(buff));
        printf("The information received by the parent process is: %s\n",buff) ;
    }

    return 0;
}