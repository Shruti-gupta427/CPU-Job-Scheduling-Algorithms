// Question 3. Implementation of Peterson’s Solution
// Question:
// Implement Peterson’s Algorithm to solve the critical section
// problem for two processes.
// Two threads should repeatedly try to enter the critical
// section using Peterson’s solution and update a shared
// counter.

#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

bool flag[2] = {false, false};  // intention flags
int turn;                      // whose turn
int counter = 0;               // shared variable

void process(int id) {
    int other = 1 - id;
    for (int i = 0; i < 3; i++) {
        flag[id] = true;
        turn = other;
        while (flag[other] && turn == other) {
            // busy waiting
        }

        // Critical Section
        cout << "Thread " << id + 1 << " entering critical section\n";
        counter++;
        this_thread::sleep_for(chrono::milliseconds(500));
        cout << "Thread " << id + 1 << " leaving critical section\n";
        // Exit section
        flag[id] = false;
        this_thread::sleep_for(chrono::milliseconds(200));
    }
}

int main() {
    thread t1(process, 0);
    thread t2(process, 1);
    t1.join();
    t2.join();
    cout << "Final Counter Value: " << counter << endl;
    return 0;
}
