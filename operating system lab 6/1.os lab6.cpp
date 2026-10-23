#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
using namespace std;
using namespace chrono;

int main() {
    const int n = 2000000;
    vector<long long> a(n, 1);
    auto start = steady_clock::now();
    long long sequential = 0;
    for (int i = 0; i < n; ++i) sequential += a[i];
    auto mid = steady_clock::now();

    int T;
    cout << "Enter thread count (1, 2, 4, or 8): ";
    cin >> T;
    if (T < 1 || T > 8) return 0;
    vector<long long> partial(T, 0);
    vector<thread> workers;
    int chunk = (n + T - 1) / T;
    auto pstart = steady_clock::now();
    for (int t = 0; t < T; ++t) {
        workers.emplace_back([&, t]() {
            int lo = t * chunk;
            int hi = min(n, (t + 1) * chunk);
            for (int i = lo; i < hi; ++i) partial[t] += a[i];
        });
    }
    for (auto &w : workers) w.join();
    long long parallel = 0;
    for (long long x : partial) parallel += x;
    auto pend = steady_clock::now();
    cout << "Sequential sum: " << sequential << "\nParallel sum: " << parallel;
    cout << "\nSequential time (ms): " << duration<double, milli>(mid-start).count();
    cout << "\nParallel time (ms): " << duration<double, milli>(pend-pstart).count() << "\n";
    return 0;
}
