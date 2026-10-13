#include <iostream>
#include <thread>
using namespace std;

void child_routine() {
    cout << "Child executing with unique thread ID" << endl;
}

int main() {
    thread t(child_routine);
    t.join();
    cout << "Main thread finished after joining child." << endl;
    return 0;
}