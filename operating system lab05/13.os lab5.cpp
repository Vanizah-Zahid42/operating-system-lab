
#include <iostream>
using namespace std;

int main() {
    cout << "Windows has no direct equivalent of Linux "
            "prctl(PR_SET_CHILD_SUBREAPER).\n";
    cout << "A Linux subreaper can adopt orphaned descendants.\n";
    cout << "This behavior cannot be reproduced exactly in native "
            "Windows Dev-C++.\n";
    return 0;
}
