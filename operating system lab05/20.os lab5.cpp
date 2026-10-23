
#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc > 1) {
        string mode = argv[1];
        if (mode == "normal") {
            cout << "Child 1: Normal termination.\n";
            return 0;
        }
        if (mode == "custom") {
            cout << "Child 2: Custom exit code 15.\n";
            return 15;
        }
        if (mode == "abnormal") {
            cout << "Child 3: Simulated abnormal termination.\n" << flush;
            TerminateProcess(GetCurrentProcess(), 0xC0000005);
            return 1;
        }
    }

    const char* modes[] = {"normal", "custom", "abnormal"};
    PROCESS_INFORMATION pi[3] = {};
    STARTUPINFOA si[3] = {};

    for (int i = 0; i < 3; ++i) {
        si[i].cb = sizeof(si[i]);
        string command = "\"" + string(argv[0]) + "\" " + modes[i];
        vector<char> cmd(command.begin(), command.end());
        cmd.push_back('\0');

        if (!CreateProcessA(NULL, cmd.data(), NULL, NULL, FALSE, 0,
                            NULL, NULL, &si[i], &pi[i])) {
            cout << "Failed to create child " << i + 1 << '\n';
            pi[i].hProcess = NULL;
        }
    }

    for (int i = 0; i < 3; ++i) {
        if (!pi[i].hProcess)
            continue;

        WaitForSingleObject(pi[i].hProcess, INFINITE);
        DWORD exitCode = 0;
        GetExitCodeProcess(pi[i].hProcess, &exitCode);

        cout << "Harvested Child " << i + 1
             << " | Exit code: " << exitCode;
        if (exitCode == 0)
            cout << " -> Clean termination";
        else if (exitCode == 15)
            cout << " -> Custom exit code";
        else
            cout << " -> Abnormal termination";
        cout << '\n';

        CloseHandle(pi[i].hThread);
        CloseHandle(pi[i].hProcess);
    }

    cout << "All child processes monitored.\n";
    return 0;
}
