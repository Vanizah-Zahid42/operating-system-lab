
#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[]) {
    int level = (argc > 1) ? atoi(argv[1]) : 0;
    cout << "Process at level " << level
         << ", PID = " << GetCurrentProcessId() << '\n';

    if (level >= 2)
        return 0;

    PROCESS_INFORMATION pi[2] = {};
    STARTUPINFOA si[2] = {};

    for (int i = 0; i < 2; ++i) {
        si[i].cb = sizeof(si[i]);
        string command = "\"" + string(argv[0]) + "\" " + to_string(level + 1);
        vector<char> cmd(command.begin(), command.end());
        cmd.push_back('\0');

        if (!CreateProcessA(NULL, cmd.data(), NULL, NULL, FALSE, 0,
                            NULL, NULL, &si[i], &pi[i])) {
            cout << "Failed to create child at level " << level + 1 << '\n';
        }
    }

    for (int i = 0; i < 2; ++i) {
        if (pi[i].hProcess) {
            WaitForSingleObject(pi[i].hProcess, INFINITE);
            CloseHandle(pi[i].hThread);
            CloseHandle(pi[i].hProcess);
        }
    }
    return 0;
}
