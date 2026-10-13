#include <iostream>
#include <thread>
#include <functional>
using namespace std;

void worker(int val, int &ref) {
    val = val + 10;
    ref = ref + 10;
    cout << "Inside thread: value copy = " << val
         << ", reference value = " << ref << endl;
}

int main() {
    int local_x = 5;
    int local_y = 10;

    thread t(worker, local_x, ref(local_y));
    t.join();

    cout << "After thread: local_x = " << local_x << endl;
    cout << "After thread: local_y = " << local_y << endl;
    return 0;
}