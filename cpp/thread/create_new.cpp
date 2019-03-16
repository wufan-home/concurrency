#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

extern "C"
{
    #include <stdio.h>
}

#define g_size 100
#define num_of_thread 3

using namespace std;

struct ConcurrentList
{
    explicit ConcurrentList(int length) : 
        m_list(vector<int>(length, 1)), 
        m_current(0) {}

    vector<int> m_list;
    int m_current;
};

void thread_func(ConcurrentList &l, const string &thread_id)
{
    while (l.m_current < l.m_list.size())
        printf("The thread %s moved the index %d.\n", thread_id.c_str(), l.m_current++);
}

void thread_func_cpp(ConcurrentList &l, const string &thread_id)
{
    while(l.m_current < l.m_list.size())
        cout << "(C++) The thread " << thread_id << " moved the index " << l.m_current++ << endl;
}

int main()
{
    cout << "This is the program to show how to create a thread in C++ 11." << endl;

    ConcurrentList cl(g_size);

    thread t1(thread_func, std::ref(cl), "writer");
    thread t2(thread_func, std::ref(cl), "reader");

    t1.join();
    t2.join();

    cl.m_current = 0;

    thread t3(thread_func_cpp, std::ref(cl), "writer");
    thread t4(thread_func_cpp, std::ref(cl), "reader");

    t3.join();
    t4.join();
    
    return 1;
}
