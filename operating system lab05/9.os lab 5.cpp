#include <iostream>
#include <windows.h>
#include <string>
#include <cstring>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc > 1 && string(argv[1]) == "child") {
        cout << "Child exiting immediately (PID: "
             << GetCurrentProcessId() << ")" << endl;
        return 0;
    }

    STARTUPINFOA si = {};
    PROCESS_INFORMATION pi = {};
    si.cb = sizeof(si);

    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);

    string cmd = string("\"") + path + "\" child";
    char* command = new char[cmd.length() + 1];
    strcpy_s(command, cmd.length() + 1, cmd.c_str());

    if (!CreateProcessA(NULL, command, NULL, NULL, FALSE,
                        CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
        cout << "Child process creation failed!" << endl;
        delete[] command;
        return 1;
    }

    delete[] command;

    cout << "Parent sleeping 20 seconds without waiting." << endl;
    cout << "Child PID: " << pi.dwProcessId << endl;

    Sleep(20000);

    WaitForSingleObject(pi.hProcess, INFINITE);

    cout << "Child process handle released." << endl;

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}