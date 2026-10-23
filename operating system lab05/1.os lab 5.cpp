
#include <iostream>
#include <windows.h>

using namespace std;

int main() {
    // Get current process ID (Parent)
    DWORD parentPID = GetCurrentProcessId();

    // Create a child process
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    char command[] = "cmd.exe /c echo Child Process created";

    if (!CreateProcess(
        NULL,
        command,
        NULL,
        NULL,
        FALSE,
        CREATE_NO_WINDOW,
        NULL,
        NULL,
        &si,
        &pi
    )) {
        cout << "Process creation failed!" << endl;
        return 1;
    }

    // Parent process information
    cout << "Parent Process -> PID: " << parentPID
         << " | Child PID: " << pi.dwProcessId << endl;

    // Wait for child process to finish
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Child process information
    cout << "Child Process -> PID: " << pi.dwProcessId
         << " | Parent PID: " << parentPID << endl;

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}
