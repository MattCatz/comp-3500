
# 1) What happens to a thread when it exits (i.e., calls thread_exit() )? What about
when it sleeps?
When a thread exits first we check that our stack was not blown out. Next we turn off interupts. Next we destory the threads address space and vnode. Finally we decrement the number of threads, mark the thread as a zombie and perform a context switch.

When a thread sleeps we need an adress that can wake us up. Next we check that we are not in an inturupt handler. Finally we set out status to sleep and perform a context switch.

# 2) What function(s) handle(s) a context switch?
mi\_switch(threadstate\_t nextstate) handles context switching. This is machine-independent meaning that it is a high level context switching algorithm that should work on any platform.

# 3) How many thread states are there? What are they?
There are four thread states. They are S\_RUN, S\_READY, S\_SLEEP, and S\_ZOMB.

# 4) What does it mean to turn interrupts off? How is this accomplished? Why is it important to turn off interrupts in the thread subsystem code?
Turrning off interrupts mean setting the priority bit to highest value. This is accomplished using the splhigh function provided in spl.h. Turning off interrupts in the thread subsystem code is important because some actions need to be atomic and thus not interrupted. For example inturupts must be off to sleep a thread or else they may sleep forevery.

# 5) What happens when a thread wakes up another thread? How does a sleeping thread get to run again?
When a thread is being woken up we first check that inturupts are turning off. Then we look through the array of thread an see if any of them have the wakeup adress we are looking for. Note that one adress can wake up multiple threads. Each thread is made runnable using make\_runnable in scheduler.h.

A sleeping thread will wake up again when its sleep adress is passed to thread\_wakeup in thread.h. thread\_wakeup will make the thread runnable by putting it at the end of the scheduler's queue using make\_runnable.

# 6) What function is responsible for choosing the next thread to run?
The function scheduler is defined in scheduler.h is responsible for finding the next thread to run.

# 7) How does that function pick the next thread?
It currently uses a round robin algorithm so each thread gets equal time running (no priorities).

# 8) What role does the hardware timer play in scheduling? What hardware independent function is called on a timer interrupt?
The hardware timer, called hardclock, is used as a forced context switch. The hardware independent function is also called hardclock and is defined in hardclock.h.

# 9) Describe how thread\_sleep() and thread\_wakeup() are used to implement semaphores.
Thread\_sleep is used in the wait function of the semaphore. Thread\_wakeup is used in the signal function of the seaphore.

The address argument is used kinda like a key. Thread\_sleep assosiates that adress with the sleeping thread. Thread\_wakeup uses that adress to find the threads, notice can be more than one, assosiated with that address and only wake up those.

# 10) Why does the lock API in OS/161 provide lock\_do\_i\_hold(), but not lock\_get\_holder()?
It is done that way because a lock should only be released by the holder.