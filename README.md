### Task 3: Java Race Condition

When I run the code, the final result for bar is not 20000. It give a random smaller number like 18432 or 19100. 

This happen because the operation bar++ is not atomic. The computer actually do it in 3 steps:
1. Read the current value of bar
2. Add 1 to this value
3. Write the new value back to memory

Because we have two threads running in same time without protection, sometimes Thread 1 and Thread 2 read the value at the exact same moment. For example, if they both read 5, they both add 1, and they both write 6. We just lost one addition. This problem is call a "Race Condition".




### Task 4: Fix with Synchronized Method

When I run the code with the changes, the output is exactly 20000 everytime. 

This is because the keyword synchronized put a lock on the method. 
It mean only one thread can be inside the baz() function at the same time. If Thread 1 is doing bar++, Thread 2 have to wait outside until Thread 1 finish. Because they wait their turn, no additions are lost and the race condition is fixed.




### Task 5: Fix with Synchronized Block

When I use synchronized(this) inside the method, the result is also 20000. 

The difference with Task 4 is that we don't lock the whole method, we just lock the specific line of code that are dangerous (the critical section). If we have a very big method with a lot of code, locking the whole method is bad for performance. With synchronized(this), we only block the other threads for the bar++ operation, so the rest of the method can run in same time. It is much more efficient.



### Task 6: Performance without locks

When I run this code with 10 threads and 10 millions iterations each, the output is something like 20046753 and 31 ms.

The first number is the result of bar. It is completely wrong (it should be 100 000 000) because there is no synchronized keyword, so there is a huge race condition and we lose millions of additions. 
The second number is the time in milliseconds. It is very fast because threads don't wait for any lock. They just write in memory as fast as possible without caring about other threads.



### Task 7: Performance with locks

When I run the code with synchronized(this), the output for bar is exactly 100000000. It is perfectly correct because the threads don't crush each other anymore.

But the time is very slow (5743 ms). This show the cost of thread safety. Everytime a thread want to do bar++, it have to take the lock and all the other threads have to wait. Doing this queue 100 millions times take a lot of CPU time. The lesson is that locks guarantee exact numbers, but they destroy performance.