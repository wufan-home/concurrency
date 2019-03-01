#include <iostream>
#include <string>
#include <thread>
#include <chrono>

using namespace std;


void thread_fn(int n)
{
    if (n == 2)
    {
        thread t4(thread_fn, 4);
        t4.join();
    }
    this_thread::sleep_for(chrono::seconds(n));
    cout << "The thread " << n << " is executing." << this_thread::get_id() << endl;
}

int main()
{
    cout << "This is the program to show how to create a thread in C++ 11." << endl;

    thread t1(thread_fn, 1);
    thread t2(thread_fn, 2);
    thread t3(thread_fn, 3);

    t1.join();
    t2.join();
    t3.join();

    return 1;
}
