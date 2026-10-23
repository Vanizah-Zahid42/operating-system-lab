#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <iomanip>
using namespace std;
using namespace chrono;

int main() {
    const int n = 4000000;
    vector<int> A(n, 1);
    double t1 = 0;
    cout << fixed << setprecision(3);
    for (int T = 1; T <= 8; ++T) {
        auto start = steady_clock::now();
        vector<long long> partial(T, 0);
        int chunk = (n + T - 1) / T;
        vector<thread> workers;
        for (int t = 0; t < T; ++t) {
            workers.emplace_back([&, t]() {
                int lo = t * chunk, hi = min(n, (t + 1) * chunk);
                for (int i = lo; i < hi; ++i) partial[t] += A[i];
            });
        }
        for (auto &w : workers) w.join();
        double elapsed = duration<double, milli>(steady_clock::now() - start).count();
        if (T == 1) t1 = elapsed;
        cout << "T=" << T << " time(ms)=" << elapsed << " speedup=" << (elapsed > 0 ? t1 / elapsed : 0)
             << " efficiency=" << (elapsed > 0 ? t1 / elapsed / T : 0) << "\n";
    }
    return 0;
}
