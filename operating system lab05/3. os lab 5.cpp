#include <iostream>
#include <windows.h>
#include <string>
#include <cstring>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc > 1 && string(argv[1]) == "child1") {
        cout << "First Sibling running with PID: "
             << GetCurrentProcessId() << endl;
        return 0;
    }

    if (argc > 1 && string(argv[1]) == "child2") {
        cout << "Second Sibling running with PID: "
             << GetCurrentProcessId() << endl;
        return 0;
    }

    STARTUPINFOA si = {};
    PROCESS_INFORMATION p1 = {}, p2 = {};
    si.cb = sizeof(si);

    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);

    string cmd1 = string("\"") + path + "\" child1";
    char* command1 = new char[cmd1.length() + 1];
    strcpy_s(command1, cmd1.length() + 1, cmd1.c_str());

    if (!CreateProcessA(NULL, command1, NULL, NULL, FALSE, 0,
                        NULL, NULL, &si, &p1)) {
        cout << "First child creation failed!" << endl;
        delete[] command1;
        return 1;
    }
    delete[] command1;

    string cmd2 = string("\"") + path + "\" child2";
    char* command2 = new char[cmd2.length() + 1];
    strcpy_s(command2, cmd2.length() + 1, cmd2.c_str());

    if (!CreateProcessA(NULL, command2, NULL, NULL, FALSE, 0,
                        NULL, NULL, &si, &p2)) {
        cout << "Second child creation failed!" << endl;
        delete[] command2;
        WaitForSingleObject(p1.hProcess, INFINITE);
        CloseHandle(p1.hProcess);
        CloseHandle(p1.hThread);
        return 1;
    }
    delete[] command2;

    WaitForSingleObject(p1.hProcess, INFINITE);
    WaitForSingleObject(p2.hProcess, INFINITE);

    CloseHandle(p1.hProcess);
    CloseHandle(p1.hThread);
    CloseHandle(p2.hProcess);
    CloseHandle(p2.hThread);

    return 0;
}