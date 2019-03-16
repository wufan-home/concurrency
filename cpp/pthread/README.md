In this folder, we shall collect the sample code about multi-thread model in C++ (earlier thatn C++ 11). Before C++ 11, C++ does not natively support the multi-thread model. It requires the library pthread.h to fulfill the goal.

## Content
**condition_variable.cpp**: [code]() <br>
Show the usage of condition variable. Condition variable is the most used tool to synchronize threads. It should be used together with mutexes or locks.

**create.cpp**: [code]() <br>
Show how to create instances. In C++ 11, threads are defined as class but not an integer in the older version of C++. Refer the repository [pthread]().

**deadlock.cpp**: [code]()<br>
Give an example of dead lock. The reason is not to call the unlock function before break.

**lock_guard.cpp**: [code]() <br>
Show the usage of lock_guard.

**mutex.cpp**: [code]() <br>
Show the usage of mutex. The basic usage of mutex is first to call ```try_lock``` function and then call ```unlock``` when exit from the mutex region. Mutex is also used to create a lock.

**racing_condition.cpp**: [code]() <br>
Give an example of racing condition. The sample output can be found in [output]().

**reentrant_lock.cpp**: [code]() <br>

**rw_lock**: [code]() <br>

**scoped_lock.cpp**: [code]() <br>

**shared_lock.cpp**: [code]() <br>
Show the usage of shared_lock.

**unique_lock.cpp**: [code]() <br>
Show the usage of unique lock. Unique lock is the lock which can only be accessed by the thread which claims it.

## Reference
