#include <iostream>
#include <vector>
#include <thread>
using namespace std;

int main() {
    int n, T;
    cout << "Enter number of elements: ";
    cin >> n;
    cout << "Enter thread count: ";
    cin >> T;
    if (n <= 0 || T <= 0) return 0;
    vector<int> A(n);
    for (int i = 0; i < n; ++i) A[i] = (i * 37) % 10000;
    A[n / 2] = 99999;
    int chunk = (n + T - 1) / T;
    vector<int> localMax(T, -2147483647);
    vector<thread> workers;
    for (int t = 0; t < T; ++t) {
        workers.emplace_back([&, t]() {
            int lo = t * chunk, hi = min(n, (t + 1) * chunk);
            for (int i = lo; i < hi; ++i) if (A[i] > localMax[t]) localMax[t] = A[i];
        });
    }
    for (auto &w : workers) w.join();
    int answer = localMax[0];
    for (int t = 1; t < T; ++t) if (localMax[t] > answer) answer = localMax[t];
    cout << "Maximum element: " << answer << "\n";
    return 0;
}
