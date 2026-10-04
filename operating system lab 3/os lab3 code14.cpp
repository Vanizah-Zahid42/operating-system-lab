#include <iostream>
#include <windows.h>
#include <cstring>
using namespace std;
int main() {
    const char* mappingName = "Local\\OSLabSharedMemoryDemo";
    const DWORD SIZE = 1024;
    HANDLE mapping = CreateFileMappingA(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE,
                                        0, SIZE, mappingName);
    if (mapping == NULL) { cerr << "CreateFileMapping failed: " << GetLastError() << endl; return 1; }
    char* data = (char*)MapViewOfFile(mapping, FILE_MAP_ALL_ACCESS, 0, 0, SIZE);
    if (data == NULL) { cerr << "MapViewOfFile failed." << endl; CloseHandle(mapping); return 1; }
    const char payload[] = "OS Shared Memory Payload";
    memcpy(data, payload, sizeof(payload));
    cout << "Data written to shared memory: " << data << endl;
    cout << "A second process can open the named mapping to read this data." << endl;
    UnmapViewOfFile(data);
    CloseHandle(mapping);
}
