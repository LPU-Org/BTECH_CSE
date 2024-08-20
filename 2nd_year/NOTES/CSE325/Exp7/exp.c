#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<pthread.h>

int shared = 1;

void* func1() {
	int x;
	x = shared;
	x += 1;
	sleep(5);
	shared = x;
	printf("Value of Shared in Func1 : %d\n",shared);
	pthread_exit(NULL);
}

void* func2() {
	int y;
	y = shared;
	y -= 1;
	sleep(5);
	shared = y;
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
