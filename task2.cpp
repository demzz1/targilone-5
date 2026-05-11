#include <iostream>
#include <thread>
#include <unistd.h> // For the sleep(5) from your slide
#include <mutex>    // 1. The library for the Mutex

using namespace std;

mutex mtx; // 2. We declare our "talking stick" globally

void foo(int a) {
    sleep(5); // The 20 threads sleep for 5 seconds at the same time

    mtx.lock();   // 3. The thread LOCKS access to the screen
    cout << a << endl;
    mtx.unlock(); // 4. The thread UNLOCKS access for others
}

int main() {
    thread threads[20];

    for (int i = 0; i < 20; i++) {
        threads[i] = thread(foo, i);
    }

    for (int i = 0; i < 20; i++) {
        threads[i].join();
    }

    return 0;
}