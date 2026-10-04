#include <iostream>
#include <windows.h>
#include <string>
using namespace std;

int main() {
    SECURITY_ATTRIBUTES sa = {sizeof(SECURITY_ATTRIBUTES), NULL, TRUE};
    HANDLE readPipe = NULL, writePipe = NULL;
    if (!CreatePipe(&readPipe, &writePipe, &sa, 0)) {
        cerr << "CreatePipe failed: " << GetLastError() << endl; return 1;
    }
    const char message[] = "Hello Child from Windows Pipe";
    DWORD written = 0;
    if (!WriteFile(writePipe, message, sizeof(message), &written, NULL))
        cerr << "WriteFile failed." << endl;
    CloseHandle(writePipe);
    char buffer[256] = {}; DWORD readBytes = 0;
    if (ReadFile(readPipe, buffer, sizeof(buffer)-1, &readBytes, NULL))
        cout << "Read from pipe: " << buffer << endl;
    CloseHandle(readPipe);
}
