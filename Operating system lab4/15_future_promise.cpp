#include <iostream>
#include <thread>
#include <future>
using namespace std;

void worker(promise<int> prom) {
    int data = 42;
    cout << "Worker computed result: " << data << endl;
    prom.set_value(data);
}

int main() {
    promise<int> prom;
    future<int> fut = prom.get_future();

    thread t(worker, move(prom));

    cout << "Main is waiting for the result..." << endl;
    int result = fut.get();

    t.join();

    cout << "Main received result: " << result << endl;
    return 0;
}