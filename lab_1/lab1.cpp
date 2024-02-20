#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <cerrno> 
#include <cstring> 

using namespace std;

void * threadFunc1(void *arg)
{	
	cout << "Второй поток начал работу"<< endl;
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
	cout << "Второй поток начал работу"<< endl;
	bool *flag = (bool*) arg;
	while(*flag==1)
	{
	putchar('2');
	fflush(stdout);
	sleep(1);
	}
	pthread_exit((void*)2);
}
//Изменения - добавлена визуализация работы программы согласно требованиям МУ.
//Изменения - 1)выполнено требование, добавлены атрибуты потоков(ранее запускались с NULL
//Изменения - 2)у второго потока подобран атрибут, чтобы pthread_join выдала системную ошибку, её код выведен на экран
int main()
{
	cout << "Программа начала работу"<< endl;
	bool flag1 = 1;
	bool flag2 = 1;
	int *exitCode1;
	int *exitCode2;
	pthread_t thread1;
	pthread_t thread2;
    	pthread_attr_t attr; 
    	pthread_attr_init(&attr);
    	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED); 

    	pthread_create(&thread1, NULL, threadFunc1, &flag1);
    	pthread_create(&thread2, &attr, threadFunc2, &flag2);
	cout << "Нажмите <Enter> для завершения работы потоков"<< endl;
	getchar();
	cout << "Клавиша нажата"<< endl;
	flag1=0;
	flag2=0;



	int joinResult1 = pthread_join(thread1,(void**)&exitCode1);
	int joinResult2 = pthread_join(thread2,(void**)&exitCode2);
	
	if(joinResult1)
	{
	cout << "Первый pthread_join завершился с ошибкой "<< strerror(joinResult1)<< " " << joinResult1 << endl;
	}
	else
	{
	cout << "Первый поток завершил работу с кодом "<< exitCode1 << endl;
	}
	
	if(joinResult2)
	{
	cout << "Второй pthread_join завершился с ошибкой "<< strerror(joinResult2) << " " << joinResult2 << endl;
	}
	else
	{
	cout << "Второй поток завершил работу с кодом "<< exitCode2 << endl;
	}
	

	pthread_attr_destroy(&attr); 
	cout << "Программа завершила работу" << endl;
	
}
