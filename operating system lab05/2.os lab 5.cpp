
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <string>

using namespace std;

int counter = 100;

int main(int argc, char* argv[]) {

   
    if (argc > 1 && string(argv[1]) == "child") {
        counter += 50;

        cout << "[Child] counter = " << counter
             << " at address: " << (void*)&counter << endl;

        return 0;
    }

    
    STARTUPINFOA si = {};
    PROCESS_INFORMATION pi = {};
    si.cb = sizeof(si);

    char command[] = "cmd.exe /c \"\"";

    
    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);

    string cmd = string("\"") + path + "\" child";
    char* commandLine = new char[cmd.length() + 1];
    strcpy_s(commandLine, cmd.length() + 1, cmd.c_str());

    if (!CreateProcessA(
        NULL, commandLine, NULL, NULL, FALSE,
        CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {

        cout << "Process creation failed!" << endl;
        delete[] commandLine;
        return 1;
    }

    delete[] commandLine;

    Sleep(1000);

    cout << "[Parent] counter = " << counter
         << " at address: " << (void*)&counter << endl;

  
    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}
