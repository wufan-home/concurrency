#include <chrono>
#include <iostream>
#include <mutex>
extern "C"
{
    #include <stdio.h> 
}
#include <string>
#include <thread>
#include <vector>

using namespace std;

#define thread_num 2
#define memeory_size 10
#define sleep_second 3

mutex g_mutex;  // Global lock.

class Param
{
public:
    Param(vector<int> *shared_memory, const string &thread_name): 
        m_thread_name(thread_name),
        m_shared_memory(shared_memory), 
        m_size(shared_memory->size()),
        m_current(0) {} 

    const string m_thread_name;
    vector<int> *m_shared_memory;
    int m_size;
    int m_current;
};

void thread_func(void *param)
{
    Param *pm = (Param *)param;

    printf("Enter the %s thread.\n", pm->m_thread_name.c_str());
    
    while(1)
    {
        if(g_mutex.try_lock())
        {
            this_thread::sleep_for(chrono::seconds(1));
            
            if (pm->m_current < pm->m_size)
                printf("The %s thread read the %d th element from the shared memeory\n", pm->m_thread_name.c_str(), pm->m_current++);
            else
                break;

            g_mutex.unlock();
        }
    }
}

int main()
{
    cout << "This program shows how to use mutex to sync." << endl;

    vector<int> shared_memory(memeory_size, 0);

    Param *p1 = new Param(&shared_memory, "reader");
    thread writer_t(thread_func, p1);

    Param *p2 = new Param(&shared_memory, "writer");
    thread reader_t(thread_func, p2);

    writer_t.join();
    reader_t.join();

    cout << "Exit from the main thread." << endl;
    return 1;
}
