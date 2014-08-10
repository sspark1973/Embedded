/*
Print Process IDs for Threads

Here¡¯s what the output might look like:
% cc thread-pid.c -o thread-pid -lpthread
% ./thread-pid &
[1] 14608
main thread pid is 14608
child thread pid is 14610

% ps x
PID TTY STAT TIME COMMAND
14042 pts/9 S 0:00 bash
14608 pts/9 R 0:01 ./thread-pid
14609 pts/9 S 0:00 ./thread-pid
14610 pts/9 R 0:01 ./thread-pid
14611 pts/9 R 0:00 ps x

% kill 14608
[1]+ Terminated ./thread-pid

Notice that there are three processes running the thread-pid program.
	The first of these, with pid 14608, is the main thread in the program; 
	the third, with pid 14610, is the thread we created to execute thread_function.
	How about the second thread, with pid 14609? 
		This is the ¡°manager thread,¡± which is part of the internal implementation of GNU/Linux threads.
		The manager thread is created the first time a program calls pthread_create to create a new thread.

For instance, if a program forks and the child process execs a multithreaded program, 
the parent process will hold the process id of the main thread of the child process¡¯s program 
and will use that process id to send signals to its child.

This is generally a good convention to follow yourself when sending signals to a multithreaded program.

Although GNU/Linux threads created in the same program are implemented as separate processes, 
they share their virtual memory space and other resources.

A child process created with fork, however, gets copies of these items.

The Linux clone system call is a generalized form of fork and pthread_create that
allows the caller to specify which resources are shared between the calling process and
the newly created process. Also, clone requires you to specify the memory region for
the execution stack that the new process will use.Although we mention clone here to
satisfy the reader¡¯s curiosity, that system call should not ordinarily be used in programs.
Use fork to create new processes or pthread_create to create threads.


*/

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *thread_function(void *args)
{
	fprintf(stderr, "Child thread pid is %d\n", (int) getpid());

	/* Spin forever */
	while (1);
	return NULL;
}

int main()
{  
	pthread_t thread;
	fprintf (stderr, "main thread pid is %d\n", (int) getpid());

	pthread_create (&thread, NULL, &thread_function, NULL);

	/* Spin forever */
	while (1);
	return 0;
}


