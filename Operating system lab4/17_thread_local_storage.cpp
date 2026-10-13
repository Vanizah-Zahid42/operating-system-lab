#include <iostream>
#include <thread>
#include <vector>
using namespace std;

thread_local int txn_id = 0;

void run(int id) {
    txn_id++;
    cout << "Thread " << id << " has its own txn_id = " << txn_id << endl;
    txn_id++;
    cout << "Thread " << id << " now has txn_id = " << txn_id << endl;
}

int main() {
    vector<thread> threads;
    for (int i = 1; i <= 3; ++i)
        threads.push_back(thread(run, i));

    for (size_t i = 0; i < threads.size(); ++i)
        threads[i].join();

    cout << "Each thread maintained its own thread-local variable." << endl;
    return 0;
}