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
    ¦   m_shared_memory(vector<int>(length, 0)),
    ¦   m_count(0),
    ¦   m_process(true),
    ¦   m_update(false) {}

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
    ¦   unique_lock<mutex> process_lock(cl.m_mutex);
    ¦   while(!cl.m_process)
    ¦   ¦   cl.m_cv.wait(process_lock);

    ¦   cl.m_shared_memory[2] = cl.m_shared_memory[0] + cl.m_shared_memory[1];
    ¦
    ¦   cl.m_update = true;
    ¦   cl.m_process = false;
