// Question 2. Synchronization Without Busy Waiting
// (Semaphore / Mutex)
// Question:
// Implement a synchronization mechanism without busy
// waiting using a semaphore or mutex to control access to a
// critical section.
// The program should create multiple threads that access a
// shared variable safely.

#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex mtx;          
int counter = 0;   

void criticalSection(int threadId) {
    for (int i = 0; i < 3; i++) {

        // Acquire lock
        mtx.lock();
        cout << "Thread " << threadId << " acquired lock" << endl;

        // Critical Section
        counter++;
        this_thread::sleep_for(chrono::milliseconds(500));

        // Release lock
        cout << "Thread " << threadId << " released lock" << endl;
        mtx.unlock();
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
