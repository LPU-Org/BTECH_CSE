#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<pthread.h>
#include<semaphore.h>

int shared = 1;
sem_t s;

void* func1() {
	int x;
	sem_wait(&s);
	x = shared;
	x += 1;
	sleep(5);
	shared = x;
	sem_post(&s);
	printf("Value of Shared in Func1 : %d\n",shared);
	pthread_exit(NULL);
}

void* func2() {
	int y;
	sem_wait(&s);
	y = shared;
	y -= 1;
	sleep(5);
	shared = y;
	sem_post(&s);
	printf("Value of Shared in Func2 : %d\n",shared);
	pthread_exit(NULL);
}

int main() {
	int n;
	sem_init(&s,0,1);
	pthread_t t1, t2;
	pthread_create(&t1,NULL,func1,NULL);
	pthread_create(&t2,NULL,func2,NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	return 0;
}
