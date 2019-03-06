#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

using namespace std;

struct ThreadParameter
{
    ThreadParameter(vector<int> *shared, int *index, const string& thread_name) 
        : m_shared(shared), 
          m_size(shared->size()), 
          m_current(index), 
          m_thread_name(thread_name){}

    vector<int> *m_shared;
    int m_size;
    int *m_current;
    string m_thread_name;
};

void thread_fn(void *param)
{
    ThreadParameter *l_param = (ThreadParameter *) param;
    while (*(l_param->m_current) < l_param->m_size)
    {
        printf("This is the thread %s, show the value at index %d. \n", 
               l_param->m_thread_name.c_str(), 
               ++(*(l_param->m_current)));
    }
}

int main()
{
    cout << "This is the program to show how to create a thread in C++ 11." << endl;

    vector<int> shared(100, 1);
    int index = 0;

    ThreadParameter param1(&shared, &index, "first");
    thread t1(thread_fn, &param1);

    ThreadParameter param2(&shared, &index, "second");
    thread t2(thread_fn, &param2);

    ThreadParameter param3(&shared, &index, "third");
    thread t3(thread_fn, &param3);

    t1.join();
    t2.join();
    t3.join();

    return 1;
}
