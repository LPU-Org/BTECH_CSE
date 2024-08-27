#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<pthread.h>

char data[] = "CSE325";
pthread_mutex_t p;
char* rec;

void* client() {
    printf("Client: Sending a request to the server.\n");
	pthread_mutex_lock(&p);
	sleep(1);
    rec = data;
    printf("Client: Recieved a response from the server.\n");
	pthread_mutex_unlock(&p);
	pthread_exit(NULL);
}

void* server() {
    printf("Server: Received a request, processing...\n");
    printf("Server: Sending a response to the client.\n");
	pthread_mutex_lock(&p);
	pthread_mutex_unlock(&p);
	pthread_exit(NULL);
}

int main() {
	int n;
	pthread_t t1, t2;
	pthread_create(&t1,NULL,client,NULL);
	pthread_create(&t2,NULL,server,NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
    printf("Recieved Data: %s\n", rec);
	return 0;
}
