/*
GNU/Linux implements the POSIX standard thread API (known as pthreads)
All thread functions and data types are declared in the header file <pthread.h>

The pthread functions are not included in the standard C library. 
Instead, they are in libpthread.so, you should add -lpthread to the command line when you link your program.

You need to specify the library on the gcc/g++ command line after the files that depend on the library.
For most gcc options order doesn't matter, but for libraries it's critical.


gcc .\thread.c -o thread -lpthread

pthread_create - create a new thread

#include <pthread.h>

int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                   void *(*start_routine) (void *), void *arg);

*/


#include <pthread.h>
#include <stdio.h>
#include <errno.h>

struct char_print_parms
{
	char character;
	int count;
};

void *char_print(void *parameters)
{
	struct char_print_parms *p = (struct char_print_parms *) parameters;
	int i;

	for (i = 0; i < p->count; ++i)
		fputc(p->character, stderr);

	return NULL;
}

void *print_xs (void *unused)
{
	while (1)
		fputc('x', stderr);

	return NULL;
}

int main()
{
	pthread_t thread_id;
	pthread_t thread_id2;

	struct char_print_parms thread1_args;
	struct char_print_parms thread2_args;

	thread1_args.character = 'K';
	thread1_args.count = 30;
	pthread_create(&thread_id, NULL, &char_print, &thread1_args);

	thread2_args.character = '9';
	thread2_args.count = 20;
	pthread_create(&thread_id2, NULL, &char_print, &thread2_args);

/*
	What¡¯s to prevent Linux from scheduling the three threads in such a
	way that main finishes executing before either of the other two threads are done?
	Nothing! But if this happens, the memory containing the thread parameter structures
	will be deallocated while the other two threads are still accessing it.

	One solution is to force main to wait until the other two threads are done.
	-> pthread_join
*/

/*
	That function is pthread_join, which takes two arguments: 
		the thread ID of the thread to wait for, and 
		a pointer to a void* variable that will receive the finished

	thread¡¯s return value. 
	If you don¡¯t care about the thread return value, pass NULL as the second argument.
*/

	/* Make sure the first thread has finished. */
	pthread_join(thread_id, NULL);
	/* Make sure the second thread has finished. */
	pthread_join(thread_id2, NULL);

	//pthread_create (&thread_id, NULL, &print_xs, NULL);

	//while (1)
	//	fputc('o', stderr);
	
	return 0;
}
