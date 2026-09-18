#include<iostream>
#include <windows.h>
using namespace std;
int main()
{



 STARTUPINFOA si{};
 PROCESS_INFORMATION pi{};
si.cb =sizeof(si);

 char command[] =
 "cmd.exe /C echo I amthe child";

 if(CreateProcessA(
 nullptr,
 command,
 nullptr,
 nullptr,
 FALSE,
 0,
 nullptr,
 nullptr,
 &si,
 &pi)) {

 std::cout << "I amtheparent\n";

 CloseHandle(pi.hThread);
 CloseHandle(pi.hProcess);
 }
}
