#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void logger() {
    for (int i = 1; i <= 3; ++i) {
        cout << "Logger: flushing buffer to disk..." << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }
    cout << "Logger thread finished." << endl;
}

int main() {
    cout << "Starting background logger..." << endl;
    thread t(logger);
    t.detach();

    cout << "Main continues without joining logger." << endl;
    this_thread::sleep_for(chrono::seconds(4));
    cout << "Main thread finished." << endl;
    return 0;
}