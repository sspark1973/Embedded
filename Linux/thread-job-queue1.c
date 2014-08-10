/*
Debugging a threaded program is difficult because you cannot always easily reproduce
the behavior that caused the problem.You might run the program once and have
everything work fine; the next time you run it, it might crash.There¡¯s no way to make
the system schedule the threads exactly the same way it did before.

The ultimate cause of most bugs involving threads is that the threads are accessing
the same data.

These bugs are called race conditions; 
	the threads are racing one another to change the same data structure.
*/

/*
Thread Function to Process Jobs from the Queue

GNU/Linux provides mutexes, 
short for MUTual EXclusion locks.
A mutex is a special lock that only one thread may lock at a time.
	pthread_mutex_t mutex;
	pthread_mutex_init (&mutex, NULL);
	or
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_lock / pthread_mutex_unlock

Mutexes provide a mechanism for allowing one thread to block the execution of another.
This opens up the possibility of a new class of bugs, called deadlocks.
A deadlock occurs when one or more threads are stuck waiting for something that never will occur.

	pthread_mutexattr_t attr;
	pthread_mutex_t mutex;
	pthread_mutexattr_init (&attr);
	pthread_mutexattr_setkind_np (&attr, PTHREAD_MUTEX_ERRORCHECK_NP); // PTHREAD_MUTEX_RECURSIVE_NP
	pthread_mutex_init (&mutex, &attr);
	pthread_mutexattr_destroy (&attr);

pthread_mutex_trylock

	if the mutex is already locked by another thread, pthread_mutex_trylock will not block.
	Instead, it will return immediately with the error code EBUSY.The mutex lock held by
	the other thread is not affected.You may try again later to lock the mutex.

We¡¯ve shown how to use a mutex to protect a variable against simultaneous access by
two threads and how to use semaphores to implement a shared counter.


*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

struct job {
	struct job *next;

	/* Other fields describing work to be done... */
};

struct job *job_queue;

/* A mutex protecting job_queue. */
pthread_mutex_t job_queue_mutex = PTHREAD_MUTEX_INITIALIZER;

/* A semaphore counting the number of jobs in the queue. */
sem_t job_queue_count;

void initialize_job_queue()
{
	job_queue = NULL;
	/* Initialize the semaphore which counts jobs in the queue. Its
		initial value should be zero. */
	sem_init(&job_queue_count, 0, 0);
}

void process_job(struct job *j)
{
	printf("%s Called\n", __FUNCTION__);
	return;
}

void *thread_function(void *args)
{
	while(1) {
		/* Get the next available job. */
		struct job *next_job;

		/* Wait on the job queue semaphore. If its value is positive,
			indicating that the queue is not empty, decrement the count by
			1. If the queue is empty, block until a new job is enqueued. */
		sem_wait(&job_queue_count);

		printf("%s : Pass sem_wait job_queue_count[%d]\n", __FUNCTION__, job_queue_count);

		/* Lock the mutex on the job queue. */
		pthread_mutex_lock(&job_queue_mutex);

		/* Because of the semaphore, we know the queue is not empty. Get
			the next available job. */
		next_job = job_queue;
		/* Remove this job from the list. */
		job_queue = job_queue->next;

		/* Unlock the mutex on the job queue because we¡¯re done with the
			queue for now. */
		pthread_mutex_unlock(&job_queue_mutex);

		/* Carry out the work. */
		process_job(next_job);
		free(next_job);
	}
	return NULL;
}

void enqueue_job(/* Pass job-specific data here */)
{
	struct job *new_job;

	new_job = (struct job*)malloc(sizeof(struct job));

	pthread_mutex_lock(&job_queue_mutex);

	/* Place the new job at the head of the queue. */
	new_job->next = job_queue;
	job_queue = new_job;

	/* Post to the semaphore to indicate that another job is available. If
		threads are blocked, waiting on the semaphore, one will become
		unblocked so it can process the job. */
	printf("%s : Calling sem_post\n", __FUNCTION__);
	sem_post(&job_queue_count);

	pthread_mutex_unlock(&job_queue_mutex);
}

int main()
{
	pthread_t thread;

	initialize_job_queue();
	pthread_create(&thread, NULL, &thread_function, NULL);
	//pthread_join(thread, NULL);

	enqueue_job();

	while(1) {
		enqueue_job();
	}

	return 0;
}



