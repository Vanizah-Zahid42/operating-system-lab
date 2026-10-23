#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
using namespace std;
using namespace chrono;

int main() {
    int N, T;
    cout << "Enter matrix size (suggested 100): ";
    cin >> N;
    cout << "Enter thread count: ";
    cin >> T;
    if (N <= 0 || T <= 0) return 0;
    vector<vector<long long> > A(N, vector<long long>(N, 1));
    vector<vector<long long> > B(N, vector<long long>(N, 2));
    vector<vector<long long> > C(N, vector<long long>(N, 0));
    auto start = steady_clock::now();
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            for (int k = 0; k < N; ++k) C[i][j] += A[i][k] * B[k][j];
    auto mid = steady_clock::now();
    for (int i = 0; i < N; ++i) fill(C[i].begin(), C[i].end(), 0);
    int rows = (N + T - 1) / T;
    vector<thread> workers;
    auto pstart = steady_clock::now();
    for (int t = 0; t < T; ++t) {
        workers.emplace_back([&, t]() {
            int lo = t * rows, hi = min(N, (t + 1) * rows);
            for (int i = lo; i < hi; ++i)
                for (int j = 0; j < N; ++j)
                    for (int k = 0; k < N; ++k) C[i][j] += A[i][k] * B[k][j];
        });
    }
    for (auto &w : workers) w.join();
    auto pend = steady_clock::now();
    cout << "C[0][0] = " << C[0][0] << "\n";
    cout << "Sequential time (ms): " << duration<double, milli>(mid-start).count();
    cout << "\nParallel time (ms): " << duration<double, milli>(pend-pstart).count() << "\n";
    return 0;
}
