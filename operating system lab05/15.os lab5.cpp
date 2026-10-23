
#include <iostream>
#include <windows.h>
using namespace std;

int main() {
    STARTUPINFOA si = {};
    PROCESS_INFORMATION pi = {};
    si.cb = sizeof(si);

   
    char env[] = "LAB_MODULE=OS_PROC\0SEM=FALL2026\0\0";
    char command[] = "cmd.exe /c echo LAB_MODULE=%LAB_MODULE% ^& echo SEM=%SEM%";

    if (!CreateProcessA(NULL, command, NULL, NULL, FALSE, 0,
                        env, NULL, &si, &pi)) {
        cout << "Failed to start child process.\n";
        return 1;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    return 0;
}
