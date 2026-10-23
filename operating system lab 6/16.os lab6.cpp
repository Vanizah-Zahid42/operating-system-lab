#include <iostream>
using namespace std;

struct UserTask {
    int id;
    int steps;
};
int main() {
    const int k = 4;
    UserTask tasks[k] = {{1, 5}, {2, 5}, {3, 5}, {4, 5}};
    bool finished[k] = {false, false, false, false};
    int remaining = k;
    cout << "Cooperative user-level thread simulation on Windows\n";
    cout << "All tasks run in this one program thread; each gives up control after one step.\n";
    while (remaining > 0) {
        for (int i = 0; i < k; ++i) {
            if (!finished[i]) {
                cout << "User thread " << tasks[i].id << " step " << (6 - tasks[i].steps) << "\n";
                --tasks[i].steps;
                if (tasks[i].steps == 0) {
                    finished[i] = true;
                    --remaining;
                }
            }
        }
    }
    cout << "All cooperative user tasks finished.\n";
    cout << "This is a portable round-robin simulation, not ucontext.h, which is not available in standard Windows Dev-C++.\n";
    return 0;
}
