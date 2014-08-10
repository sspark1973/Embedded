/*
Implementing Safe Thread Exit with C++ Exceptions

If a thread calls pthread_exit, though, C++ doesn¡¯t guarantee that destructors are
called for all automatic variables on the thread¡¯s stack. A clever way to recover this
functionality is to invoke pthread_exit at the top level of the thread function by
throwing a special exception.
*/

#include <pthread.h>
#include <stdio.h>

class ThreadExitException
{
public:
	ThreadExitException(void *return_value)
		: thread_return_value_(return_value)
	{
		fprintf(stderr, "%s Called!\n", __FUNCTION__);
	}

	void *DoThreadExit()
	{
		fprintf(stderr, "%s Called!\n", __FUNCTION__);
		pthread_exit(thread_return_value_);
	}

private:
	void *thread_return_value_;
};

void do_some_work() 
{
	while(1) {
		//if(should_exit_thread_immediately())
			throw ThreadExitException (/* thread's return value = */ NULL );
	}
}

void *thread_function(void *args)
{
	try {
		do_some_work();
	}
	catch (ThreadExitException ex) {
		ex.DoThreadExit();
	}

	return NULL;
}

int main()
{
	pthread_t thread;
	pthread_create(&thread, NULL, &thread_function, NULL);

	while(1);
	return 0;
}
		

