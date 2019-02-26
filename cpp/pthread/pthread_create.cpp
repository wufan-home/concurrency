#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

using namespace std;

#define N 10
#define exit_index 4

pthread_t tid[N];

void* thread_func(void *arg)
{
        pthread_t current = pthread_self();
        sleep(1);
        int index = 0;
        for (; index < N; ++index)
                if (pthread_equal(current, tid[index]))
                {
                        printf("the %dth thread recovers from sleeping.\n", index);
                        if (index == exit_index)
                        {
                                printf("Exit from the %dth thread.\n", exit_index);
                                pthread_exit(NULL);
                        }
                        break;
                }

        for(int i = 0; i < 1000000; ++i) {
                // printf("The %dth thread is printing %d.\n", index, i);
        }

        return NULL;
}

int main()
{
        printf("This is a sample code for multi-threading programming in C/C++.\n");
        for(int i = 0; i < N; ++i)
        {
                int status = pthread_create(&(tid[i]), NULL, &thread_func, NULL);
                if (status == 0)
                        printf("The thread is created successfully: %d \n", i);
                else
                        printf("Failed.\n");
        }

        sleep(5);

        return 1;
}
