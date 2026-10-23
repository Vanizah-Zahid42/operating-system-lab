
#include <iostream>
#include <windows.h>
#include <string>
#include <cstring>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc > 1 && string(argv[1]) == "child") {
        Sleep(3000);
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

    if (!CreateProcessA(NULL, command, NULL, NULL, FALSE, 0,
                        NULL, NULL, &si, &pi)) {
        cout << "Child process creation failed!" << endl;
        delete[] command;
        return 1;
    }

    delete[] command;

    while (true) {
        DWORD result = WaitForSingleObject(pi.hProcess, 0);

        if (result == WAIT_TIMEOUT) {
            cout << "Parent computing independent background tasks..." << endl;
            Sleep(500);
        }
        else if (result == WAIT_OBJECT_0) {
            cout << "Child finished! Parent wrapping up." << endl;
            break;
        }
        else {
            cout << "Error checking child process status!" << endl;
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
            return 1;
        }
    }

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}
