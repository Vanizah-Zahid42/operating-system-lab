
#include <iostream>
#include <windows.h>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc > 1 && string(argv[1]) == "child") {
        cout << "Child is running independently.\n";
        Sleep(2000);
        cout << "Child finished its work.\n";
        return 0;
    }

    STARTUPINFOA si = {};
    PROCESS_INFORMATION pi = {};
    si.cb = sizeof(si);
    string command = "\"" + string(argv[0]) + "\" child";
    char cmd[2048];
    strcpy_s(cmd, sizeof(cmd), command.c_str());

    if (!CreateProcessA(NULL, cmd, NULL, NULL, FALSE, 0,
                        NULL, NULL, &si, &pi)) {
        cout << "Failed to start child.\n";
        return 1;
    }

    cout << "Parent started child and exits without waiting.\n";
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    return 0;
}
