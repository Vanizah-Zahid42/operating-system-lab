#include <iostream>
#include <windows.h>
#include <string>
using namespace std;
int main() {
    cout << "Starting Windows command process to list directory..." << endl;
    STARTUPINFOA si = {}; PROCESS_INFORMATION pi = {}; si.cb = sizeof(si);
    char command[] = "cmd.exe /c dir";
    if (!CreateProcessA(NULL, command, NULL, NULL, FALSE, CREATE_NEW_CONSOLE,
                        NULL, NULL, &si, &pi)) {
        cerr << "CreateProcess failed: " << GetLastError() << endl; return 1;
    }
    WaitForSingleObject(pi.hProcess, INFINITE);
    cout << "Parent waited for command process to finish." << endl;
    CloseHandle(pi.hThread); CloseHandle(pi.hProcess);
}
