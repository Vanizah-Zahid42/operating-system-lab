
#include <iostream>
#include <windows.h>
using namespace std;

int main() {
    STARTUPINFOA si = {};
    PROCESS_INFORMATION pi = {};
    si.cb = sizeof(si);
    char command[] = "cmd.exe /c exit 0";

    if (!CreateProcessA(NULL, command, NULL, NULL, FALSE, 0,
                        NULL, NULL, &si, &pi)) {
        cout << "Failed to create child process.\n";
        return 1;
    }

    cout << "Child process started.\n";
    WaitForSingleObject(pi.hProcess, INFINITE);

    DWORD exitCode = 0;
    GetExitCodeProcess(pi.hProcess, &exitCode);
    cout << "Child finished with exit code: " << exitCode << '\n';

    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    cout << "Handles closed; parent references released.\n";
    return 0;
}
