In this folder, all code are written in C++ 11.

## Content
**condition_variable.cpp**: [code](https://github.com/wufan-home/concurrency/blob/master/cpp/thread/conditional_variable.cpp) <br>
Show the usage of condition variable. <br>
Condition variable is the most used tool to synchronize threads. It should be used together with mutexes or locks.

**create.cpp**: [code](https://github.com/wufan-home/concurrency/blob/master/cpp/thread/create.cpp) <br>
Show how to create instances. In C++ 11, threads are defined as class but not an integer in the older version of C++. Refer the repository [pthread]().

**deadlock.cpp**: [code](https://github.com/wufan-home/concurrency/blob/master/cpp/thread/deadlock.cpp)<br>
Give an example of dead lock. The reason is not to call the unlock function before break.

**lock_guard.cpp**: [code]() <br>
Show the usage of lock_guard.

**mutex.cpp**: [code](https://github.com/wufan-home/concurrency/blob/master/cpp/thread/mutex.cpp) <br>
Show the usage of mutex. The basic usage of mutex is first to call ```try_lock``` function and then call ```unlock``` when exit from the mutex region. Mutex is also used to create a lock.

**racing_condition.cpp**: [code](https://github.com/wufan-home/concurrency/blob/master/cpp/thread/racing_condition.cpp) <br>
Give an example of racing condition. The sample output can be found in [output]().

**reentrant_lock.cpp**: [code]() <br>

**rw_lock**: [code]() <br>

**scoped_lock.cpp**: [code]() <br>

**shared_lock.cpp**: [code]() <br>
Show the usage of shared_lock.

**unique_lock.cpp**: [code](https://github.com/wufan-home/concurrency/blob/master/cpp/thread/unique_lock.cpp) <br>
Show the usage of unique lock. Unique lock is the lock which can only be accessed by the thread which claims it.

## Reference
Anthony A. Williams, C++ Concurrency in Action: Practical Multithreading, 2ed, Manning Publication, 2019. [Link](https://www.manning.com/books/c-plus-plus-concurrency-in-action-second-edition)
