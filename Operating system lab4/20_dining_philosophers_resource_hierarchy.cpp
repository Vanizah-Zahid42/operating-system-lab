#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 5;
mutex forks[N];

void dine(int philosopher_id) {
    int left_id = philosopher_id;
    int right_id = (philosopher_id + 1) % N;

    int first = min(left_id, right_id);
    int second = max(left_id, right_id);

    unique_lock<mutex> l1(forks[first]);
    unique_lock<mutex> l2(forks[second]);

    cout << "Philosopher " << philosopher_id << " acquired forks "
         << first << " and " << second << " and is eating." << endl;

    this_thread::sleep_for(chrono::milliseconds(200));

    cout << "Philosopher " << philosopher_id << " finished eating." << endl;
}

int main() {
    vector<thread> philosophers;

    for (int i = 0; i < N; ++i)
        philosophers.push_back(thread(dine, i));

    for (size_t i = 0; i < philosophers.size(); ++i)
        philosophers[i].join();

    cout << "All philosophers finished without circular deadlock." << endl;
    return 0;
}