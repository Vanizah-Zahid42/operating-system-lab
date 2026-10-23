#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
using namespace std;

long long dot = 0;
mutex m;

int main() {
    int n, T;
    cout << "Enter number of elements: ";
    cin >> n;
    cout << "Enter thread count: ";
    cin >> T;
    if (n <= 0 || T <= 0) return 0;
    vector<int> A(n, 2), B(n, 3);
    int chunk = (n + T - 1) / T;
    vector<thread> workers;
    for (int t = 0; t < T; ++t) {
        workers.emplace_back([&, t]() {
            int lo = t * chunk, hi = min(n, (t + 1) * chunk);
            long long p = 0;
            for (int i = lo; i < hi; ++i) p += 1LL * A[i] * B[i];
            lock_guard<mutex> lock(m);
            dot += p;
        });
    }
    for (auto &w : workers) w.join();
    cout << "Dot product with mutex: " << dot << "\n";
    cout << "Expected sequential result: " << 6LL * n << "\n";
    cout << "Remove the lock_guard to observe the race-prone version (result may or may not differ).\n";
    return 0;
}
