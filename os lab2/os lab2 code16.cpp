#include <iostream>
#include <windows.h>

LONG WINAPI ExceptionHandler(EXCEPTION_POINTERS* ExceptionInfo) {
    std::cout << "Hardware memory protection trap caught!\n";
    return EXCEPTION_CONTINUE_EXECUTION;
}

int main() {
    char* page = (char*)VirtualAlloc(
        nullptr,
        4096,
        MEM_COMMIT,
        PAGE_READWRITE
    );

    if (page == nullptr)
        return 1;

    page[0] = 'A';

    // Change memory to read-only
    DWORD oldProtect;

    VirtualProtect(
        page,
        4096,
        PAGE_READONLY,
        &oldProtect
    );

    // Install exception handler
    PVOID handler = AddVectoredExceptionHandler(1, ExceptionHandler);

    // This write causes a memory protection exception
    page[0] = 'B';

    // Remove exception handler
    RemoveVectoredExceptionHandler(handler);

    VirtualFree(page, 0, MEM_RELEASE);

    return 0;
}