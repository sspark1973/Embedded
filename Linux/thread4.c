/*
Unlike process, all threads in a single program share the same address space.
This means that if one thread modifies a location in memory 
(for instance, a global variable), the change is visible to all other threads.
This allows multiple threads to operate on the same data without the use interprocess communication mechanisms 

Each thread has its own call stack, however. 
This allows each thread to execute different code and to call and return from subroutines in the usual way.

As in a single threaded program, 
each invocation of a subroutine in each thread has its own set of local variables, which are stored on the stack for that thread.

Sometimes, however, it is desirable to duplicate a certain variable so that each thread has a separate copy.
GNU/Linux supports this by providing each thread with a thread-specific data area.
The variables stored in this area are duplicated for each thread,
and each thread may modify its copy of a variable without affecting other threads.


*/

#include <pthread.h>
#include <stdio.h>
//#include <stdlib.h>
//#include <malloc.h>

/* The key used to associate a log file pointer with each thread. */
static pthread_key_t thread_log_key;

void write_to_thread_log (const char *message)
{
	FILE *thread_log = (FILE *) pthread_getspecific (thread_log_key);
	fprintf (thread_log, "%s\n", message);
}

void close_thread_log (void *thread_log)
{
	fclose((FILE *)thread_log);
}

void *thread_function(void *arg)
{
	char thread_log_filename[20];
	FILE *thread_log;
	pthread_t self_id = pthread_self();

	sprintf(thread_log_filename, "thread%u.log", self_id);

	thread_log = fopen(thread_log_filename, "w");

	/* Store the file pointer in thread-specific data under thread_log_key. */
	pthread_setspecific (thread_log_key, thread_log);

	write_to_thread_log("Thread starting.");

	return NULL;
}

int main()
{
	int i;
	pthread_t threads[5];

	/* Create a key to associate thread log file pointers in
	thread-specific data. Use close_thread_log to clean up the file
	pointers. */
	pthread_key_create (&thread_log_key, close_thread_log);

	for (i = 0; i < 5; ++i)
		pthread_create (&threads[i], NULL, thread_function, NULL);

	for (i = 0; i < 5; ++i)
		pthread_join (threads[i], NULL);

	return 0;
}
