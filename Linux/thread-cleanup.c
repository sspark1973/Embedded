/*
Program Fragment Demonstrating a Thread

A cleanup handler is a temporary measure, used to deallocate a resource only if the
thread exits or is canceled instead of finishing execution of a particular region of code.
Under normal circumstances, when the thread does not exit and is not canceled, the
resource should be deallocated explicitly and the cleanup handler should be removed.

To register a cleanup handler, call pthread_cleanup_push, passing a pointer
to the cleanup function and the value of its void* argument.The call to

	pthread_cleanup_push must be balanced by a corresponding call to
	pthread_cleanup_pop, which unregisters the cleanup handler

*/


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Allocate a temporary buffer */
void *allocate_buffer(size_t size)
{
	fprintf(stderr, "%s called !\n", __FUNCTION__);
	return malloc(size);
}

// Deallocate a temporary buffer
void deallocate_buffer(void *buffer)
{
	fprintf(stderr, "%s called !\n", __FUNCTION__);
	free(buffer);
}

void do_some_work ()
{
	/* Allocate a temporary buffer. */
	void *temp_buffer = allocate_buffer(1024);

	/* Register a cleanup handler for this buffer, to deallocate it in
		case the thread exits or is cancelled. */
	pthread_cleanup_push(deallocate_buffer, temp_buffer);

	/* Do some work here that might call pthread_exit or might be
	cancelled... */
	fprintf(stderr, "%s called !\n", __FUNCTION__);

	/* Unregister the cleanup handler. Because we pass a nonzero value,
		this actually performs the cleanup by calling
		deallocate_buffer. */
	pthread_cleanup_pop(1);
}

void *thread_function(void *args)
{
	do_some_work();
	return NULL;
}

int main()
{
	pthread_t thread;
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_create(&thread, &attr, &thread_function, NULL);

	while(1);
	

	return 0;
}
