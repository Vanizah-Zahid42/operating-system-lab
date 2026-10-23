#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int count;
    cout << "How many measurements? ";
    cin >> count;
    cout << fixed << setprecision(4);
    for (int i = 0; i < count; ++i) {
        double N, S;
        cout << "Enter thread count N (>1) and measured speedup S: ";
        cin >> N >> S;
        if (N <= 1 || S <= 0) {
            cout << "Invalid measurement.\n";
            continue;
        }
        double f = (1.0 / S - 1.0 / N) / (1.0 - 1.0 / N);
        cout << "Estimated serial fraction f = " << f << "\n";
    }
    return 0;
}
