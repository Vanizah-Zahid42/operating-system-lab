#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <cmath>
#include <chrono>
using namespace std;
using namespace chrono;

void taskX() {
    volatile double x = 0;
    for (int i = 1; i < 1500000; ++i) x += sqrt((double)i);
}
void taskY() {
    vector<int> a(400000);
    for (int i = 0; i < (int)a.size(); ++i) a[i] = (a.size() - i) % 100003;
    sort(a.begin(), a.end());
}
int main() {
    auto start = steady_clock::now();
    thread t1(taskX), t2(taskY);
    t1.join(); t2.join();
    cout << "Two independent tasks completed concurrently.\n";
    cout << "Elapsed time (ms): " << duration<double, milli>(steady_clock::now() - start).count() << "\n";
    cout << "Windows Dev-C++ alternative: std::thread is used instead of OpenMP sections.\n";
    return 0;
}
