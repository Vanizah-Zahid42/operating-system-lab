#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    double p;
    cout << "Enter parallel fraction p (0 to 1, not including 0): ";
    cin >> p;
    if (p <= 0 || p > 1) {
        cout << "Invalid p.\n";
        return 0;
    }
    cout << fixed << setprecision(4);
    for (int N = 1; N <= 16; ++N) {
        double speedup = (p == 1.0) ? N : 1.0 / ((1.0 - p) + p / N);
        cout << "Threads: " << N << "  Speedup: " << speedup << "\n";
    }
    return 0;
}
