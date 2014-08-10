/*
Thread attributes provide a mechanism for fine-tuning the behavior of individual
threads.
	1. Create a pthread_attr_t object
	2. Call pthread_attr_init
	3. Modify the attribute object
	4. Pass a pointer to the attribute object when calling pthread_create
	5. Call pthread_attr_destroy to release the attribute object.

Thread Cancellation
	Under normal circumstances, 
	a thread terminates when it exits normally, either by returning from its thread function or by calling pthread_exit.

	To cancel a thread, call pthread_cancel, passing the thread ID of the thread to be canceled.

	A canceled thread may later be joined; in fact, you should join a canceled thread to free up its resources, 
	unless the thread is detached (see Section 4.1.5,¡°Thread Attributes¡±).

	The return value of a canceled thread is the special value given by PTHREAD_CANCELED.

	A thread may be in one of three states with regard to thread cancellation.
		pthread_setcanceltype (PTHREAD_CANCEL_ASYNCHRONOUS, NULL); // Asynchronous cancel - anytime
		pthread_setcanceltype (PTHREAD_CANCEL_DEFERRED, NULL); // can cancel in running state -> queue
		pthread_setcancelstate (PTHREAD_CANCEL_DISABLE, NULL);
		pthread_setcancelstate (PTHREAD_CANCEL_ENABLE, NULL);

*/
#include <stdio.h>
#include <pthread.h>

float *account_balances;

int process_transaction (int from_acct, int to_acct, float dollars)
{
	int old_cancel_state;

	if (account_balances[from_acct] < dollars)
		return 1;

	/* Begin critical Section */
	pthread_setcancelstate (PTHREAD_CANCEL_DISABLE, &old_cancel_state);
	account_balances[to_acct] += dollars;
	account_balances[from_acct] -= dollars;
	pthread_setcancelstate (old_cancel_state, NULL);

	return 0;
}

void *thread_function(void *arg)
{
	printf("%s called\n", __FUNCTION__);
	return NULL;
}



int main(void)
{
	pthread_attr_t attr;
	pthread_t thread;

	pthread_attr_init(&attr);
	/*
	Even if a thread is created in a joinable state, it may later be turned into a detached thread.
	To do this, call pthread_detach.
	Once a thread is detached, it cannot be made joinable again.
	*/

	/*
	the thread¡¯s exit state hangs around in the system (kind of like a zombie process) 
	until another thread calls pthread_join to obtain its return value. Only then are its resources released.

	A detached thread, in contrast, is cleaned up automatically when it terminates.
	joinable thread - default
	*/
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_create(&thread, &attr, &thread_function, NULL);
	pthread_attr_destroy(&attr);

	/* No need to join the second thread */
	return 0;
}

