#include <iostream>
#include <thread>
using namespace std;
long long counter = 0;
void increment_task() { for (int i=0; i<100000; ++i) ++counter; }
int main() {
    thread t1(increment_task), t2(increment_task);
    t1.join(); t2.join();
    cout << "Expected: 200000 | Actual counter: " << counter << endl;
    cout << "Note: the unsynchronized result is not guaranteed." << endl;
}
