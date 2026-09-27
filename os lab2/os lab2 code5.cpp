#include <iostream>
#include <windows.h>

int main() {
    // Step 1: Reserve 1 MB of virtual addresses (no RAM allocated yet)
    void* base = VirtualAlloc(
        nullptr,
        1024 * 1024,
        MEM_RESERVE,
        PAGE_NOACCESS
    );

    if (!base)
        return 1;

    std::cout << "Reserved 1 MB address space at: " << base << "\n";

    // Step 2: Back the first 4 KB page with actual physical RAM
    int* page = (int*)VirtualAlloc(
        base,
        4096,
        MEM_COMMIT,
        PAGE_READWRITE
    );

    if (!page) {
        VirtualFree(base, 0, MEM_RELEASE);
        return 1;
    }

    page[0] = 42; // Now safe to read and write

    std::cout << "Committed memory value: " << page[0] << "\n";

    // Clean up
    VirtualFree(base, 0, MEM_RELEASE);

    return 0;
}