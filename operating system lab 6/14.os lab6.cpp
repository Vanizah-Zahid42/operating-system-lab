#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    double p;
    cout << "Enter estimated parallel fraction p (0 to 1): ";
    cin >> p;
    if (p < 0 || p > 1) return 0;
    cout << fixed << setprecision(4);
    for (int N = 1; N <= 8; ++N) {
        double amdahl = (p == 1.0) ? N : 1.0 / ((1.0-p) + p/N);
        double gustafson = N - (1.0-p) * (N-1);
        cout << "N=" << N << " Amdahl=" << amdahl << " Gustafson=" << gustafson << "\n";
    }
    cout << "Amdahl assumes a fixed problem size; Gustafson assumes the problem grows with the number of processors.\n";
    return 0;
}
