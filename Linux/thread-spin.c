/*
We¡¯ve shown how to use a mutex to protect a variable against simultaneous access by
two threads and how to use semaphores to implement a shared counter.

A condition variable is a third synchronization device that GNU/Linux provides; 
with it, you can implement more complex conditions under which threads execute.

A Simple Condition Variable Implementation

*/

#include <pthread.h>
#include <stdio.h>

/*
A condition variable enables you to implement a condition under which a thread executes
and, inversely, the condition under which the thread is blocked.
*/

int thread_flag;
pthread_cond_t thread_flag_cv;
pthread_mutex_t thread_flag_mutex;

void initialize_flag()
{
	pthread_mutex_init(&thread_flag_mutex, NULL);
	pthread_cond_init(&thread_flag_cv, NULL);
	thread_flag = 0;
}

void do_work()
{
	printf("%s : Called!\n", __FUNCTION__);
	return;
}

void *thread_function(void *args)
{
	int number = *(int *)args;
	printf("%s : number [%d]\n", __FUNCTION__, number);

	while(1) {
		//int flag_is_set;

		pthread_mutex_lock(&thread_flag_mutex);

		while(!thread_flag) {
			/* The flag is clear. Wait for a signal on the condition
				variable, indicating that the flag value has changed. When the
				signal arrives and this thread unblocks, loop and check the
				flag again. */
			pthread_cond_wait(&thread_flag_cv, &thread_flag_mutex);
		}
		// flag_is_set = thread_flag;
		//printf("%s : flag_is_set[%d]!\n", __FUNCTION__, flag_is_set);
		printf("%s : thread_flag_cv[%d]!\n", __FUNCTION__, thread_flag_cv);

		/* When we¡¯ve gotten here, we know the flag must be set. Unlock
			the mutex. */
		pthread_mutex_unlock(&thread_flag_mutex);
		//if(flag_is_set)
		do_work();
		break;
	}
	return (void*)number;
}

void set_thread_flag(int flag_value)
{
	pthread_mutex_lock(&thread_flag_mutex);
	/* Set the flag value, and then signal in case thread_function is
		blocked, waiting for the flag to become set. However,
		thread_function can¡¯t actually check the flag until the mutex is
		unlocked. */
	thread_flag = flag_value;
	pthread_cond_signal(&thread_flag_cv);
	pthread_mutex_unlock(&thread_flag_mutex);
}

int main()
{
	pthread_t thread;
	int a = 10;
	int b;

	initialize_flag();
	pthread_create(&thread, NULL, thread_function, &a);

	set_thread_flag(123);
	
	pthread_join(thread, (void *)&b);

	printf("%s : return b[%d]\n", __FUNCTION__, b);

	//while(1);
	return 0;
}


