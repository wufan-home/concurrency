#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

int g_value(0);

mutex g_mutex;

void thread_fn(int n)
{
    cout << "Enter the thread " << n << endl;
    while(1)
    {
    ¦   if(g_mutex.try_lock())
    ¦   {
    ¦   ¦   this_thread::sleep_for(chrono::seconds(n));
    ¦   ¦   cout << "The thread " << n << " change the value: "<< ++g_value << endl;
    ¦   ¦   g_mutex.unlock();
    ¦   ¦   break;
    ¦   }
    }
}

int main()
{
    cout << "This program shows how to use mutex to sync." << endl;


    thread t1(thread_fn, 1);
    thread t2(thread_fn, 2);

    t1.join();
    t2.join();

    cout << "Exit from the main thread." << endl;
    return 1;
}
