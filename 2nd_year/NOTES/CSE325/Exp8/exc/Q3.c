#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_SIZE 512

struct message {
    long mtype;
    char mtext[MAX_SIZE];
};

int main() {
    int msg_id;
    struct message msg;
    char buff[15] = "Hello World!!!";

    msg_id = msgget((key_t)123, 0666 | IPC_CREAT);

    if (msg_id == -1) {
        printf("ID could not be generated...");
        exit(1);
    }

    msg.mtype = 1;
    strcpy(msg.mtext, buff);
    msgsnd(msg_id, &msg, MAX_SIZE, 0);
    printf("Data sent: %s\n", msg.mtext);

    if (fork() == 0) {
        msgrcv(msg_id, &msg, MAX_SIZE, 1, 0);
        printf("Data received: %s\n", msg.mtext);
        exit(0);
    } else {
        wait(NULL);
        msgctl(msg_id, IPC_RMID, 0);
        exit(0);
    }

    return 0;
}
