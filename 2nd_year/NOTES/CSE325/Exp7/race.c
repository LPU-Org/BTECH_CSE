#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<pthread.h>

int shared = 1;
pthread_mutex_t p;

void* func1() {
	int x;
	pthread_mutex_lock(&p);
	x = shared;
	x += 1;
	sleep(5);
	shared = x;
	pthread_mutex_unlock(&p);
	printf("Value of Shared in Func1 : %d\n",shared);
	pthread_exit(NULL);
}

void* func2() {
	int y;
	pthread_mutex_lock(&p);
	y = shared;
	y -= 1;
	sleep(5);
	shared = y;
	pthread_mutex_unlock(&p);
	printf("Value of Shared in Func2 : %d\n",shared);
	pthread_exit(NULL);
}

int main() {
	int n;
	pthread_t t1, t2;
	pthread_create(&t1,NULL,func1,NULL);
	pthread_create(&t2,NULL,func2,NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	return 0;
}
