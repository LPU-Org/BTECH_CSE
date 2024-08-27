#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
    void* shm;
    int shmid;
    char buff[100];

    shmid = shmget((key_t)123, 2048, 0666|IPC_CREAT);

    printf("\nThe key value of the attached process is : %d\n", shmid);

    shm = shmat(shmid, NULL, 0);

    printf("Process attached to the address of %p\n", shm);

    // printf("Write the data to the shared memory: \n");
    // read(0, buff, 100);
    // strcpy(shm, buff);

    printf("The stored data in shared memory is: %s\n", (char*)shm);

    return 0;
}