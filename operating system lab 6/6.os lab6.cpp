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
    auto s = steady_clock::now();
    taskX(); taskY();
    auto e = steady_clock::now();
    auto p = steady_clock::now();
    thread a(taskX), b(taskY);
    a.join(); b.join();
    auto q = steady_clock::now();
    cout << "Sequential time (ms): " << duration<double, milli>(e-s).count();
    cout << "\nParallel time (ms): " << duration<double, milli>(q-p).count() << "\n";
    return 0;
}
