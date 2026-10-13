#include <iostream>
#include <thread>
#include <shared_mutex>
#include <vector>
using namespace std;

shared_mutex rw_mtx;
int data_value = 0;

void reader(int id) {
    shared_lock<shared_mutex> lock(rw_mtx);
    cout << "Reader " << id << " reads data = " << data_value << endl;
}

void writer(int value) {
    unique_lock<shared_mutex> lock(rw_mtx);
    data_value = value;
    cout << "Writer changes data to " << data_value << endl;
}

int main() {
    thread w(writer, 100);
    w.join();

    vector<thread> readers;
    for (int i = 1; i <= 3; ++i)
        readers.push_back(thread(reader, i));

    for (size_t i = 0; i < readers.size(); ++i)
        readers[i].join();

    return 0;
}