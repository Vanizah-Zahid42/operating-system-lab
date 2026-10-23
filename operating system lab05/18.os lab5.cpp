
#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc > 1 && string(argv[1]) == "child") {
        ofstream file("log.txt", ios::app);
        file << "[Child Data]\n";
        cout << "Child wrote to log.txt\n";
        return 0;
    }

    ofstream clearFile("log.txt");
    clearFile.close();

    STARTUPINFOA si = {};
    PROCESS_INFORMATION pi = {};
    si.cb = sizeof(si);
    string command = "\"" + string(argv[0]) + "\" child";
    vector<char> cmd(command.begin(), command.end());
    cmd.push_back('\0');

    if (!CreateProcessA(NULL, cmd.data(), NULL, NULL, FALSE, 0,
                        NULL, NULL, &si, &pi)) {
        cout << "Failed to create child.\n";
        return 1;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);

    ofstream file("log.txt", ios::app);
    file << "[Parent Data]\n";
    file.close();

    cout << "Parent wrote to log.txt. Check the file.\n";
    return 0;
}
