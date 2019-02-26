#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

#define N 3

pthread_t tid[N];

struct param
{
    param(const char* role) 
    {
        size = strlen(role);
        m_role = new char[size];
        strcpy(m_role, role);
    }

    ~param()
    {
        if(m_role != NULL)
        {
            delete[] m_role;
            m_role = NULL;
            size = 0;
        }
    }
	
    char* m_role;
    int size;
};

void* thread_func(void *arg)
{
	pthread_t current = pthread_self();
	sleep(1);
	int index = 0;
    TA *cur_arg = static_cast<TA *>(arg);
	for (; index < N; ++index)
    {
		if (pthread_equal(current, tid[index]))
		{
			printf("the %dth thread recovers from sleeping.\n", index);
            printf("The %d th thread is a %s thread.\n", index, cur_arg->m_thread_role.c_str());
			if (index == exit_index)
			{
				printf("Exit from the %dth thread.\n", exit_index);
				pthread_exit(NULL);
			}
			break;
		}
    }

	for(int i = 0; i < 1000000; ++i) 
    {
		// printf("The %dth thread is printing %d.\n", index, i);
	}

	return NULL;
}

int main()
{
	printf("This is a sample code for multi-threading programming in C/C++.\n");
    TA *warg = new TA("writer");
    if (pthread_create(&(tid[0]), NULL, &thread_func, warg) != 0)
    {
        printf("The writer thread failed to be created!");
    }

    TA *rarg[N - 1];
    for(int i = 1; i < N; ++i)
	{
       rarg[i - 1] = new TA("Reader");
		int status = pthread_create(&(tid[i]), NULL, &thread_func, rarg[i - 1]);
		if (status == 0)
			printf("The thread is created successfully: %d \n", i);
		else
			printf("Failed.\n");
	}

	sleep(5);

    delete warg;
    for(int i = 1; i < N; ++i)
        delete rarg[i - 1];

	return 1;
}
