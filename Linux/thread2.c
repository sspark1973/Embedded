/*
Using Thread return value

Occasionally, it is useful for a sequence of code to determine which thread is executing it.

The pthread_self function 
	returns the thread ID of the thread in which it is called.
	
	pthread_t self_id = pthread_self();
	sprintf(thread_log_filename, "thread%u.log", self_id);

This thread ID may be compared with another thread ID using the pthread_equal function.

if (!pthread_equal (pthread_self (), other_thread))
	pthread_join (other_thread, NULL);

*/


#include <pthread.h>
#include <stdio.h>

void *compute_prime(void *arg)
{
	int candidate = 2;
	int n = *((int *)arg);

	while (1) {
		int factor;
		int is_prime = 1;

		for (factor = 2; factor < candidate; ++factor) {
			if (candidate % factor == 0) {
				is_prime = 0;
				break;
			}
		}

		if (is_prime) {
			if (--n == 0) {
				printf("n = [%d]\n", n);
				return (void*) candidate;
			}
			printf("if out n = [%d]\n", n);
		}
		++candidate;
	}
	return NULL;
}
				

int main()
{
	pthread_t thread;
	int which_prime = 5000;
	int prime;

	pthread_create (&thread, NULL, compute_prime, &which_prime);
	pthread_join (thread, (void *)&prime);

	printf("The [%d]th prime number is %d.\n", which_prime, prime);
	return 0;
}
