#include <iostream>
#include <thread>
#include <vector>
#include <windows.h>
using namespace std;

void worker(int id) {
    DWORD tid = GetCurrentThreadId();
    cout << "Worker " << id << " | Process ID: " << GetCurrentProcessId()
         << " | Thread ID: " << tid << "\n";
    this_thread::sleep_for(chrono::seconds(3));
}
int main() {
    cout << "Process ID: " << GetCurrentProcessId() << "\n";
    vector<thread> workers;
    for (int i = 1; i <= 4; ++i) workers.emplace_back(worker, i);
    for (auto &t : workers) t.join();
    cout << "Each worker has a distinct Windows thread ID.\n";
    cout << "Windows equivalent uses GetCurrentThreadId; Linux /proc is not available on Windows.\n";
    return 0;
}
