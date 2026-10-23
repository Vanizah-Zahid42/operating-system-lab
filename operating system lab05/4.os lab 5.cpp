#include <iostream>
#include <windows.h>
#include <string>
#include <cstring>
#include <tlhelp32.h>

using namespace std;

DWORD GetParentProcessId() {
    DWORD ppid = 0;
    DWORD pid = GetCurrentProcessId();

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (snapshot != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32 entry;
        entry.dwSize = sizeof(entry);

        if (Process32First(snapshot, &entry)) {
            do {
                if (entry.th32ProcessID == pid) {
                    ppid = entry.th32ParentProcessID;
                    break;
                }
            } while (Process32Next(snapshot, &entry));
        }

        CloseHandle(snapshot);
    }

    return ppid;
}

int main(int argc, char* argv[]) {
    if (argc > 1 && string(argv[1]) == "grandchild") {
        cout << "[Grandchild] PID: " << GetCurrentProcessId()
             << " | Parent: " << GetParentProcessId() << endl;
        return 0;
    }

    if (argc > 1 && string(argv[1]) == "child") {
        STARTUPINFOA si = {};
        PROCESS_INFORMATION p3 = {};
        si.cb = sizeof(si);

        char path[MAX_PATH];
        GetModuleFileNameA(NULL, path, MAX_PATH);

        string cmd = string("\"") + path + "\" grandchild";
        char* command = new char[cmd.length() + 1];
        strcpy_s(command, cmd.length() + 1, cmd.c_str());

        if (!CreateProcessA(NULL, command, NULL, NULL, FALSE, 0,
                            NULL, NULL, &si, &p3)) {
            cout << "Grandchild creation failed!" << endl;
            delete[] command;
            return 1;
        }

        delete[] command;
        WaitForSingleObject(p3.hProcess, INFINITE);

        cout << "[Child 1] PID: " << GetCurrentProcessId()
             << " | Parent: " << GetParentProcessId() << endl;

        CloseHandle(p3.hProcess);
        CloseHandle(p3.hThread);
        return 0;
    }

    STARTUPINFOA si = {};
    PROCESS_INFORMATION p2 = {};
    si.cb = sizeof(si);

    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);

    string cmd = string("\"") + path + "\" child";
    char* command = new char[cmd.length() + 1];
    strcpy_s(command, cmd.length() + 1, cmd.c_str());

    if (!CreateProcessA(NULL, command, NULL, NULL, FALSE, 0,
                        NULL, NULL, &si, &p2)) {
        cout << "Child creation failed!" << endl;
        delete[] command;
        return 1;
    }

    delete[] command;
    WaitForSingleObject(p2.hProcess, INFINITE);

    cout << "[Parent] PID: " << GetCurrentProcessId() << endl;

    CloseHandle(p2.hProcess);
    CloseHandle(p2.hThread);

    return 0;
}