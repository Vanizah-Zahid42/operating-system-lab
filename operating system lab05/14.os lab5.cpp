
#include <iostream>
#include <windows.h>
using namespace std;

int main() {
    STARTUPINFOA si = {};
    PROCESS_INFORMATION pi = {};
    si.cb = sizeof(si);
    char command[] = "cmd.exe /c dir";

    cout << "Parent: starting the dir command...\n";
    if (!CreateProcessA(NULL, command, NULL, NULL, FALSE, 0,
                        NULL, NULL, &si, &pi)) {
        cout << "Could not start command.\n";
        return 1;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);
    cout << "Parent: command completed.\n";
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    return 0;
}
