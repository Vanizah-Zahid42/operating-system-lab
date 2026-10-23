#include <iostream>
#include <thread>
#include <chrono>
using namespace std;
using namespace chrono;

void emptyTask() {}
int main() {
    const int count = 1000;
    auto start = steady_clock::now();
    for (int i = 0; i < count; ++i) {
        thread t(emptyTask);
        t.join();
    }
    double threadMs = duration<double, milli>(steady_clock::now() - start).count();

    volatile int switchCount = 0;
    start = steady_clock::now();
    for (int i = 0; i < count * 100; ++i) ++switchCount;
    double userMs = duration<double, milli>(steady_clock::now() - start).count();

    cout << "Create/join " << count << " kernel threads (ms): " << threadMs << "\n";
    cout << "Simple user-space loop proxy for " << count * 100 << " switches (ms): " << userMs << "\n";
    cout << "This portable Windows comparison is illustrative; it does not use swapcontext or measure true context switches.\n";
    return 0;
}
