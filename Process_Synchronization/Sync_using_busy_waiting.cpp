// Question 1. Synchronization Using Busy Waiting (Spinlock)
// Question:
// Implement a synchronization mechanism using busy waiting
// (spinlock) to solve the critical section problem for two
// processes.
// Your program should create two threads that attempt to
// enter a critical section multiple times. Use a shared lock
// variable and busy waiting to ensure mutual exclusion.


#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
using namespace std;
atomic<bool> lock(false);
int counter = 0;
void criticalSection(int threadId) {
    for (int i = 0; i < 3; i++) {  
        cout << "Thread " << threadId << " requesting entry\n";
        while (lock.exchange(true)) {
            // busy wait
        }

        // Critical Section
        cout << "Thread " << threadId << " entering critical section\n";
        counter++;
        this_thread::sleep_for(chrono::milliseconds(500));
        cout << "Thread " << threadId << " leaving critical section\n";

        // Release lock
        lock.store(false);

        this_thread::sleep_for(chrono::milliseconds(200));
    }
}

int main() {
    thread t1(criticalSection, 1);
    thread t2(criticalSection, 2);
    t1.join();
    t2.join();
    cout << "Final Counter Value: " << counter << endl;
    return 0;
}
