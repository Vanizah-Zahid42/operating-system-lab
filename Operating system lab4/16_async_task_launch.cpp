#include <iostream>
#include <future>
#include <thread>
using namespace std;

int heavy_computation(int x) {
    cout << "Heavy computation is running asynchronously." << endl;
    this_thread::sleep_for(chrono::milliseconds(500));
    return x * x;
}

int main() {
    future<int> fut = async(launch::async, heavy_computation, 10);

    cout << "Main continues concurrent work." << endl;
    int result = fut.get();

    cout << "Final result: " << result << endl;
    return 0;
}