
#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc > 1 && string(argv[1]) == "child") {
        cout << "Child process started...\n" << flush;
        while (true) { /* Simulated long-running task */ }
    }

    STARTUPINFOA si = {};
    PROCESS_INFORMATION pi = {};
    si.cb = sizeof(si);
    string command = "\"" + string(argv[0]) + "\" child";
    vector<char> cmd(command.begin(), command.end());
    cmd.push_back('\0');

    if (!CreateProcessA(NULL, cmd.data(), NULL, NULL, FALSE, 0,
                        NULL, NULL, &si, &pi)) {
        cout << "Process creation failed!\n";
        return 1;
    }

    cout << "Parent: waiting for 3 seconds...\n";
    DWORD result = WaitForSingleObject(pi.hProcess, 3000);
    if (result == WAIT_TIMEOUT) {
        cout << "Time limit exceeded. Terminating child PID "
             << pi.dwProcessId << '\n';
        TerminateProcess(pi.hProcess, 1);
        WaitForSingleObject(pi.hProcess, INFINITE);
        cout << "Child process terminated.\n";
    } else if (result == WAIT_OBJECT_0) {
        cout << "Child finished within the time limit.\n";
    } else {
        cout << "Error while waiting for child.\n";
    }

    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    return 0;
}
