
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

int main() {
    string command;
    while (true) {
        cout << "myshell> ";
        getline(cin, command);

        if (command == "exit")
            break;
        if (command.empty())
            continue;

        string fullCommand = "cmd.exe /c " + command;
        int result = system(fullCommand.c_str());
        cout << "Command finished with code: " << result << '\n';
    }
    return 0;
}
