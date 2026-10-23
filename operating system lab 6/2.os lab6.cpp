#include <iostream>
#include <vector>
#include <thread>
#include <cmath>
using namespace std;

int main() {
    int n, T;
    cout << "Enter vector size: ";
    cin >> n;
    cout << "Enter thread count: ";
    cin >> T;
    if (n <= 0 || T <= 0) return 0;
    vector<double> A(n), B(n), C(n), D(n);
    for (int i = 0; i < n; ++i) {
        A[i] = i * 0.1;
        B[i] = i * 0.2;
        D[i] = A[i] * B[i] + sin(A[i]);
    }
    int chunk = (n + T - 1) / T;
    vector<thread> workers;
    for (int t = 0; t < T; ++t) {
        workers.emplace_back([&, t]() {
            int lo = t * chunk, hi = min(n, (t + 1) * chunk);
            for (int i = lo; i < hi; ++i) C[i] = A[i] * B[i] + sin(A[i]);
        });
    }
    for (auto &w : workers) w.join();
    bool same = true;
    for (int i = 0; i < n; ++i)
        if (fabs(C[i] - D[i]) > 1e-9) same = false;
    cout << "Sequential and parallel results match: " << (same ? "Yes" : "No") << "\n";
    cout << "First 5 results:\n";
    for (int i = 0; i < min(n, 5); ++i) cout << C[i] << " ";
    cout << "\n";
    return 0;
}
