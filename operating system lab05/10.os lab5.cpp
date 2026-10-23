
#include <iostream>
#include <windows.h>
using namespace std;

int main() {
    const int N = 5;
    PROCESS_INFORMATION pi[N] = {};
    STARTUPINFOA si[N] = {};
    bool finished[N] = {};
    int remaining = 0;

    for (int i = 0; i < N; ++i) {
        si[i].cb = sizeof(si[i]);
        char command[] = "cmd.exe /c ping 127.0.0.1 -n 2 > nul";
        if (CreateProcessA(NULL, command, NULL, NULL, FALSE, 0,
                           NULL, NULL, &si[i], &pi[i])) {
            cout << "Started child " << i + 1 << ", PID = "
                 << pi[i].dwProcessId << '\n';
            ++remaining;
        } else {
            cout << "Could not create child " << i + 1 << '\n';
        }
    }

    while (remaining > 0) {
        for (int i = 0; i < N; ++i) {
            if (pi[i].hProcess && !finished[i] &&
                WaitForSingleObject(pi[i].hProcess, 0) == WAIT_OBJECT_0) {
                DWORD exitCode = 0;
                GetExitCodeProcess(pi[i].hProcess, &exitCode);
                cout << "Child " << i + 1 << " finished, exit code "
                     << exitCode << '\n';
                CloseHandle(pi[i].hThread);
                CloseHandle(pi[i].hProcess);
                finished[i] = true;
                --remaining;
            }
        }
        Sleep(100);
    }
    cout << "All children cleaned up.\n";
    return 0;
}
