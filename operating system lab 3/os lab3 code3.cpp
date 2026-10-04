#include <iostream>
#include <windows.h>
#include <string>
using namespace std;

// Windows does not use Unix zombie-process states. This demonstrates an exited
// child whose process handle is retained until the parent collects its exit code.
int main(int argc, char* argv[]) {
    if (argc == 2 && string(argv[1]) == "--child") {
        cout << "Child process terminating now. PID = " << GetCurrentProcessId() << endl;
        return 0;
    }
    char exe[MAX_PATH]; GetModuleFileNameA(NULL, exe, MAX_PATH);
    string command = "\"" + string(exe) + "\" --child";
    STARTUPINFOA si = {}; PROCESS_INFORMATION pi = {}; si.cb = sizeof(si);
    if (!CreateProcessA(NULL, &command[0], NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        cerr << "CreateProcess failed: " << GetLastError() << endl; return 1;
    }
    cout << "Parent waiting 10 seconds before collecting child exit status." << endl;
    Sleep(10000);
    WaitForSingleObject(pi.hProcess, INFINITE);
    DWORD code; GetExitCodeProcess(pi.hProcess, &code);
    cout << "Parent collected child exit code: " << code << endl;
    CloseHandle(pi.hThread); CloseHandle(pi.hProcess);
}
