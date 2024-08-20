#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>

struct message {
    long mtype;
    char mtext[100];
};
  
int main() {
    key_t key;
    int msg_id;
    struct message msg;

    msg_id = msgget((key_t) 123, 0666 | IPC_CREAT);
    if (msg_id == -1) {
        printf("ID could not be generated...");
        exit(1);
    }

    pid_t p = fork();

    if (p == 0) {
        struct message sender_msg;
        sender_msg.mtype = 1;
        strcpy(sender_msg.mtext, "Hello World!!!");

        if (msgsnd(msg_id, &sender_msg, sizeof(sender_msg.mtext), 0) == -1) {
            printf("Error in sending the message...");
            exit(1);
        }

        printf("Message sent: %s\n", sender_msg.mtext);
        sleep(1);
    } 
    else {
        if (msgrcv(msg_id, &msg, sizeof(msg.mtext), 1, 0) == -1) {
            printf("Error in recieving the message...");
            exit(1);
        }

        printf("Received message: %s\n", msg.mtext);
    }

    msgctl(msg_id, IPC_RMID, NULL);

    return 0;
}
