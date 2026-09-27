#include <iostream>
#include <thread>
#include <mutex>

std::mutex rw_lock;

int sharedData = 100;

void reader(int id) {
    // Lock while reading
    std::lock_guard<std::mutex> lock(rw_lock);

    std::cout << "Reader " << id
              << " read value: " << sharedData << "\n";
}

void writer(int val) {
    // Lock while writing
    std::lock_guard<std::mutex> lock(rw_lock);

    sharedData = val;

    std::cout << "Writer updated value to: "
              << sharedData << "\n";
}

int main() {
    std::thread r1(reader, 1);
    std::thread r2(reader, 2);
    std::thread w1(writer, 200);
    std::thread r3(reader, 3);

    r1.join();
    r2.join();
    w1.join();
    r3.join();

    return 0;
}