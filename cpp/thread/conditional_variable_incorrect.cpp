#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

extern "C"
{
    #include <stdio.h>
}

using namespace std;

#define memeory_size 3
#define number_seq 30


struct ConcurrentList
{
    explicit ConcurrentList(int length) :
       m_shared_memory(vector<int>(length, 0)),
       m_count(0),
       m_process(true),
       m_update(false) {}

    vector<int> m_shared_memory;
    int m_count;

    mutex m_mutex;
    mutex m_mutex_update;

    condition_variable m_cv;

    bool m_process;
    bool m_update;
};

void thread_add(ConcurrentList &cl, const string &thread_name)
{
    for(cl.m_count = 0; cl.m_count < number_seq; ++cl.m_count)
    {
       unique_lock<mutex> process_lock(cl.m_mutex);
       while(!cl.m_process)
          cl.m_cv.wait(process_lock);

           cl.m_shared_memory[2] = cl.m_shared_memory[0] + cl.m_shared_memory[1];
    
       cl.m_update = true;
       cl.m_process = false;

       cl.m_cv.notify_one();
    }
}

void thread_show_and_update(ConcurrentList &cl, const string &thread_name)
{
    while(cl.m_count < number_seq)
    {
       unique_lock<mutex> update_lock(cl.m_mutex);

       while(!cl.m_update)
          cl.m_cv.wait(update_lock);
    
       printf(", %d", cl.m_shared_memory[2]);

       cl.m_shared_memory[0] = cl.m_shared_memory[1];
       cl.m_shared_memory[1] = cl.m_shared_memory[2];

       cl.m_update = false;
       cl.m_process = true;

      cl.m_cv.notify_one();
    }
}

int main()
{
    cout << "This program shows how to use mutex to sync." << endl;

    ConcurrentList cl(3);

    cl.m_shared_memory[0] = 1;
    cl.m_shared_memory[1] = 1;

    printf("The fibonacci seq is %d, %d", 1, 1);

    thread update(thread_show_and_update, std::ref(cl), "show and update thread");
    thread addition(thread_add, std::ref(cl), "adding thread");

    addition.join();
    update.join();

    printf(".\n");

    return 1;
}
