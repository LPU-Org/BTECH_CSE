#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>

int main(){
    int fd, n;
    pid_t id;
    char msg[] = "Hello World!!!";
    char buff[15];

    mkfifo("AK",0666);

    printf("# NAMED PIPE PROGRAM\n");

    id = fork();

    if (id == -1) {
        printf("Child Process cannot be created...");
        return -1;
    }

    if(id != 0){
        fd = open("AK", O_WRONLY);

        write(fd, msg, strlen(msg)+1);

        printf("Information written by Parent Process is: %s \n", msg);
        wait(NULL);
        close(fd);
    } 
    else if (id == 0) {
        fd = open("AK", O_RDONLY);

        n = read(fd, buff, sizeof(buff));

        printf("Information received by Child Process is: %s\n", buff);
        close(fd);
    }


    return 0;
}


