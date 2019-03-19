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
#define number_seq 10


struct ConcurrentList
{
    explicit ConcurrentList(int length) :
    ¦  m_shared_memory(vector<int>(length, 0)),
    ¦  m_update(false),
    ¦  m_count(0) {}

    vector<int> m_shared_memory;

    mutex m_mutex;
    condition_variable m_cv;
    bool m_update;
    int m_count;
};

void thread_add(ConcurrentList &cl, const string &thread_name)
{
    for(; cl.m_count < 10; ++cl.m_count)
    {
    ¦   this_thread::sleep_for(chrono::seconds(1));
    ¦   unique_lock<mutex> process_lock(cl.m_mutex, defer_lock);
    ¦   if(process_lock.try_lock())
    ¦   {
    ¦   ¦   cl.m_shared_memory[2] = cl.m_shared_memory[0] + cl.m_shared_memory[1];
    ¦   ¦   cl.m_update = true;
    ¦   ¦   process_lock.unlock();
    ¦   ¦   cl.m_cv.notify_one();
    ¦   }
    }
}

void thread_show_and_update(ConcurrentList &cl, const string &thread_name)
{
    while(cl.m_count < 10)
    {
    ¦  unique_lock<mutex> update_lock(cl.m_mutex);

    ¦  while(!cl.m_update)
    ¦   ¦ cl.m_cv.wait(update_lock);

    ¦  printf("update: %d\n", cl.m_shared_memory[2]);

    ¦  cl.m_shared_memory[0] = cl.m_shared_memory[1];
    ¦  cl.m_shared_memory[1] = cl.m_shared_memory[2];

    ¦  cl.m_update = false;

    ¦ cl.m_cv.notify_one();
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
