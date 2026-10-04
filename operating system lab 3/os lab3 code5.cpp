#include <iostream>
#include <windows.h>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc == 3 && string(argv[1]) == "--child") {
        int counter = stoi(argv[2]);
        counter += 50;
        cout << "Child sees shared_counter = " << counter << endl;
        return 0;
    }
    int shared_counter = 100;
    char exe[MAX_PATH]; GetModuleFileNameA(NULL, exe, MAX_PATH);
    string command = "\"" + string(exe) + "\" --child " + to_string(shared_counter);
    STARTUPINFOA si = {}; PROCESS_INFORMATION pi = {}; si.cb = sizeof(si);
    if (!CreateProcessA(NULL, &command[0], NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        cerr << "CreateProcess failed: " << GetLastError() << endl; return 1;
    }
    WaitForSingleObject(pi.hProcess, INFINITE);
    cout << "Parent sees shared_counter = " << shared_counter << endl;
    CloseHandle(pi.hThread); CloseHandle(pi.hProcess);
}
