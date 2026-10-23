#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
using namespace std;

struct Buffer {
    queue<long long> q;
    const int cap = 5;
    mutex m;
    condition_variable full, empty;
    void put(long long x) {
        unique_lock<mutex> lock(m);
        full.wait(lock, [&]() { return (int)q.size() < cap; });
        q.push(x);
        lock.unlock();
        empty.notify_one();
    }
    long long get() {
        unique_lock<mutex> lock(m);
        empty.wait(lock, [&]() { return !q.empty(); });
        long long x = q.front(); q.pop();
        lock.unlock();
        full.notify_one();
        return x;
    }
};
int main() {
    const int n = 100;
    Buffer q1, q2;
    long long answer = 0;
    thread stage1([&]() { for (int i = 1; i <= n; ++i) q1.put(i); q1.put(-1); });
    thread stage2([&]() {
        while (true) {
            long long x = q1.get();
            if (x == -1) { q2.put(-1); break; }
            q2.put(x * x);
        }
    });
    thread stage3([&]() {
        while (true) {
            long long x = q2.get();
            if (x == -1) break;
            answer += x;
        }
    });
    stage1.join(); stage2.join(); stage3.join();
    cout << "Sum of squares from 1 to " << n << " = " << answer << "\n";
    cout << "Expected result: " << 1LL * n * (n + 1) * (2 * n + 1) / 6 << "\n";
    return 0;
}
