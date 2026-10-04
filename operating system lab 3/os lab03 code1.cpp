#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc == 3 && string(argv[1]) == "--child") {
        cout << "Child Process: PID = " << GetCurrentProcessId()
             << ", Parent PID = " << argv[2] << endl;
        return 0;
    }

    char exePath[MAX_PATH];
    GetModuleFileNameA(NULL, exePath, MAX_PATH);
    DWORD parentPID = GetCurrentProcessId();

    string command = "\"" + string(exePath) + "\" --child " + to_string(parentPID);
    vector<char> cmd(command.begin(), command.end());
    cmd.push_back('\0');

    STARTUPINFOA si = {};
    PROCESS_INFORMATION pi = {};
    si.cb = sizeof(si);

    if (!CreateProcessA(NULL, cmd.data(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        cerr << "Process creation failed. Error: " << GetLastError() << endl;
        return 1;
    }

    cout << "Parent Process: PID = " << parentPID
         << ", Created Child PID = " << pi.dwProcessId << endl;
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    return 0;
}
