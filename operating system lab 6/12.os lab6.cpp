#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <iomanip>
using namespace std;
using namespace chrono;

int main() {
    const int n = 3000000;
    vector<int> A(n, 1);
    auto s = steady_clock::now();
    long long seq = 0;
    for (int x : A) seq += x;
    double tseq = duration<double, milli>(steady_clock::now() - s).count();
    double f = 0.10;
    int serialN = (int)(f * n);
    for (int T : {1, 2, 4, 8}) {
        auto start = steady_clock::now();
        long long total = 0;
        for (int i = 0; i < serialN; ++i) total += A[i];
        int remaining = n - serialN;
        int chunk = (remaining + T - 1) / T;
        vector<long long> partial(T, 0);
        vector<thread> workers;
        for (int t = 0; t < T; ++t) {
            workers.emplace_back([&, t]() {
                int lo = serialN + t * chunk;
                int hi = min(n, serialN + (t + 1) * chunk);
                for (int i = lo; i < hi; ++i) partial[t] += A[i];
            });
        }
        for (auto &w : workers) w.join();
        for (long long x : partial) total += x;
        double elapsed = duration<double, milli>(steady_clock::now() - start).count();
        cout << "T=" << T << " sum=" << total << " measured speedup=" << fixed << setprecision(3)
             << (elapsed > 0 ? tseq / elapsed : 0) << " predicted=" << 1.0 / (f + (1.0-f)/T) << "\n";
    }
    cout << "Sequential time (ms): " << tseq << "\n";
    return 0;
}
