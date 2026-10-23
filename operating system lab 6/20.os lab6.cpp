#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
using namespace std;

void userTask(int id, atomic<int> &progress) {
    for (int i = 1; i <= 5; ++i) {
        ++progress;
        cout << "User task " << id << " step " << i << "\n";
        this_thread::yield();
    }
}
void carrier(int first, atomic<int> &progress) {
    vector<thread> tasks;
    for (int id = first; id <= 20; id += 2) tasks.emplace_back(userTask, id, ref(progress));
    for (auto &t : tasks) t.join();
}
int main() {
    atomic<int> progress(0);
    cout << "M:N-style illustration: two carrier threads launch groups of user tasks.\n";
    thread c1(carrier, 1, ref(progress));
    thread c2(carrier, 2, ref(progress));
    c1.join();
    c2.join();
    cout << "Total task steps completed: " << progress << "\n";
    cout << "Note: this is a Windows-friendly illustration, not a true M:N user-thread scheduler.\n";
    cout << "Oversubscription can be tested by changing the number of worker threads relative to hardware_concurrency().\n";
    return 0;
}
