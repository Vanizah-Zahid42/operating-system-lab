#include <iostream>
#include <windows.h>
#include <string>
#include <cstring>

using namespace std;

bool CreateChild(const char* argument, PROCESS_INFORMATION &pi) {
    STARTUPINFOA si = {};
    si.cb = sizeof(si);

    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);

    string cmd = string("\"") + path + "\" " + argument;
    char* command = new char[cmd.length() + 1];
    strcpy_s(command, cmd.length() + 1, cmd.c_str());

    BOOL result = CreateProcessA(
        NULL, command, NULL, NULL, FALSE, 0,
        NULL, NULL, &si, &pi
    );

    delete[] command;
    return result != 0;
}

int main(int argc, char* argv[]) {
    if (argc > 1 && string(argv[1]) == "A") {
        Sleep(4000);
        return 10;
    }

    if (argc > 1 && string(argv[1]) == "B") {
        Sleep(1000);
        return 20;
    }

    PROCESS_INFORMATION pidA = {};
    PROCESS_INFORMATION pidB = {};

    if (!CreateChild("A", pidA)) {
        cout << "Child A creation failed!" << endl;
        return 1;
    }

    if (!CreateChild("B", pidB)) {
        cout << "Child B creation failed!" << endl;
        WaitForSingleObject(pidA.hProcess, INFINITE);
        CloseHandle(pidA.hProcess);
        CloseHandle(pidA.hThread);
        return 1;
    }

    DWORD status;

    WaitForSingleObject(pidA.hProcess, INFINITE);
    GetExitCodeProcess(pidA.hProcess, &status);
    cout << "Child A reaped with status: " << status << endl;

    WaitForSingleObject(pidB.hProcess, INFINITE);
    GetExitCodeProcess(pidB.hProcess, &status);
    cout << "Child B reaped with status: " << status << endl;

    CloseHandle(pidA.hProcess);
    CloseHandle(pidA.hThread);
    CloseHandle(pidB.hProcess);
    CloseHandle(pidB.hThread);

    return 0;
}