#include <iostream>
#include <windows.h>
#include <string>
using namespace std;
int main(int argc, char* argv[]) {
    if (argc == 3 && string(argv[1]) == "--child") {
        DWORD originalParent = static_cast<DWORD>(stoul(argv[2]));
        cout << "Child started. Original Parent PID: " << originalParent << endl;
        Sleep(3000);
        cout << "Child is still running after parent process exited. Child PID: "
             << GetCurrentProcessId() << endl;
        return 0;
    }
    char exe[MAX_PATH]; GetModuleFileNameA(NULL, exe, MAX_PATH);
    DWORD parentPID = GetCurrentProcessId();
    string command = "\"" + string(exe) + "\" --child " + to_string(parentPID);
    STARTUPINFOA si = {}; PROCESS_INFORMATION pi = {}; si.cb = sizeof(si);
    if (!CreateProcessA(NULL, &command[0], NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        cerr << "CreateProcess failed: " << GetLastError() << endl; return 1;
    }
    cout << "Parent PID: " << parentPID << " exiting without waiting." << endl;
    CloseHandle(pi.hThread); CloseHandle(pi.hProcess);
    return 0;
}
