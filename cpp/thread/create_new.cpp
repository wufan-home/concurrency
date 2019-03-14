#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

extern "C"
{
  #include <stdio.h>
}

#define size 30
#define num_of_thread 3

using namespace std;

struct ConcurrentList
{
  explicit ConcurrentList(vector<int> &in_list, int &current) :
    m_list(in_list),
    m_current(current) {}

  vector<int> &m_list;
  int &m_current;
};

void thread_func(ConcurrentList &l, const string &thread_id)
{
    if (l.m_current < l.m_list.size())
        printf("The thread %s moved the index %d.\n", thread_id.c_str(), l.m_current++);
}

int main()
{
  cout << "This is the program to show how to create a thread in C++ 11." << endl;

  vector<int> shared(100, 1);
  for(int i = 0; i < size; ++i)
    shared[i] = i;

  int shared_index = 0;

  ConcurrentList cl(std::ref(shared), std::ref(shared_index));

  return 1;
}
