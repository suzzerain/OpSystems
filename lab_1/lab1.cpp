#include <iostream>
#include <unistd.h>
#include <pthread.h>

void * threadFunc1(void *arg)
{
	bool *flag = (bool*) arg;
	while(*flag==1)
	{
	putchar('1');
	fflush(stdout);
	sleep(1);
	}
	pthread_exit((void*)1);
}
void * threadFunc2(void *arg)
{
	bool *flag = (bool*) arg;
	while(*flag==1)
	{
	putchar('2');
	fflush(stdout);
	sleep(1);
	}
	pthread_exit((void*)2);
}

int main()
{
	bool flag1 = 1;
	bool flag2 = 1;
	int *exitCode1;
	int *exitCode2;
	pthread_t thread1;
	pthread_t thread2;
	pthread_create(&thread1,NULL,threadFunc1,&flag1);
	pthread_create(&thread2,NULL,threadFunc2,&flag2);
	getchar();
	flag1=0;
	flag2=0;
	pthread_join(thread1,(void**)&exitCode1);
	pthread_join(thread2,(void**)&exitCode2);
	printf("exitcode1 = %p\n",exitCode1);
	printf("exitcode2 = %p\n",exitCode2);
}
