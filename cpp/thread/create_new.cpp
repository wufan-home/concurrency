#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

extern "C"
{
    #include <stdio.h>
}

#define g_size 30
#define num_of_thread 3

using namespace std;

struct ConcurrentList
{
    explicit ConcurrentList(int length, int current) : 
        m_list(vector<int>(length, 1)), 
        m_current(current) {}

    vector<int> m_list;
    int m_current;
};

void thread_func(ConcurrentList &l, const string &thread_id)
{
    while (l.m_current < l.m_list.size())
        printf("The thread %s moved the index %d.\n", thread_id.c_str(), l.m_current++);
}

int main()
{
    cout << "This is the program to show how to create a thread in C++ 11." << endl;

    
    int shared_index = 0;

    ConcurrentList cl(g_size, shared_index);

    thread t1(thread_func, std::ref(cl), "writer");
    thread t2(thread_func, std::ref(cl), "reader");

    t1.join();
    t2.join();

    return 1;
}
