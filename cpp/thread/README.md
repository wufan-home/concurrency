In this folder, all code are written in C++ 11.

## Content
**condition_variable.cpp**: <br>
Show the usage of condition variable. Condition variable is the most used tool to synchronize threads. It should be used together with mutexes or locks.

**create.cpp**:<br>
Show how to create instances. In C++ 11, threads are defined as class but not an integer in the older version of C++. Refer the repository [pthread]().

**deadlock.cpp**:<br>
Give an example of dead lock. The reason is not to call the unlock function before break.

**mutex.cpp**: <br>
Show the usage of mutex. The basic usage of mutex is first to call ```try_lock``` function and then call ```unlock``` when exit from the mutex region. Mutex is also used to create a lock.

**racing_condition.cpp**:<br>

**unique_lock.cpp**:<br>

## Reference
Anthony A. Williams, C++ Concurrency in Action: Practical Multithreading, 1ed, Manning Publication, 2012. [Link](https://www.manning.com/books/c-plus-plus-concurrency-in-action-second-edition)<br>
