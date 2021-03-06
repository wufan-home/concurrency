#include <chrono>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

extern "C"
{
    #include <stdio.h>
}

std::mutex g_mutex;

#define g_size 20
#define num_of_thread 2

using namespace std;

struct ConcurrentList
{
    explicit ConcurrentList(int length) : 
        m_list(vector<int>(length, 1)), 
        m_current(0) {}

    vector<int> m_list;
    volatile int m_current;
};

void thread_func(ConcurrentList &l, const string &thread_id)
{
    while(l.m_current < l.m_list.size())
    { 
        if (g_mutex.try_lock())
        {
//        printf("The current index is %d reading by the thread %s. \n", l.m_current, thread_id.c_str());
//            this_thread::sleep_for(chrono::seconds(1));

            // printf("The index %d is moved by the thread %s to be %d.\n", l.m_current++, thread_id.c_str(), l.m_current);
//            printf("The index %d is moved by the thread %s ", l.m_current, thread_id.c_str());
  //          printf("to be %d.\n", ++l.m_current);
  //
            cout << "Original value " << l.m_current << " by thread " << thread_id ;
            cout << " to be "<< ++l.m_current << endl;
            g_mutex.unlock();
        }
    }
}

int main()
{
    cout << "This is the program to show how to create a thread in C++ 11." << endl;

    ConcurrentList cl(g_size);

    thread th_list[num_of_thread];
    for(int i = 0; i < num_of_thread; ++i)
        th_list[i] = thread(thread_func, std::ref(cl), string(1, '0' + i));

    for(int i = 0; i < num_of_thread; ++i)
        th_list[i].join();

    return 1;
}
