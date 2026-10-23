#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
using namespace std;
using namespace chrono;

void busy(int ms) {
    auto end = steady_clock::now() + milliseconds(ms);
    volatile unsigned long long x = 0;
    while (steady_clock::now() < end) ++x;
}
double run(vector<int> work) {
    auto start = steady_clock::now();
    vector<thread> threads;
    for (int ms : work) threads.emplace_back(busy, ms);
    for (auto &t : threads) t.join();
    return duration<double, milli>(steady_clock::now() - start).count();
}
int main() {
    cout << "Unequal workload time (ms): " << run({100, 400, 100, 400}) << "\n";
    cout << "Balanced workload time (ms): " << run({250, 250, 250, 250}) << "\n";
    return 0;
}
