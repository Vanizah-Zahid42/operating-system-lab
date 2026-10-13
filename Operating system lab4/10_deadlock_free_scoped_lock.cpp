#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

mutex mtxA, mtxB;

void transfer_funds() {
    scoped_lock lock(mtxA, mtxB);
    cout << "Both resources acquired safely." << endl;
    cout << "Transaction executed without deadlock." << endl;
}

int main() {
    thread t1(transfer_funds);
    thread t2(transfer_funds);

    t1.join();
    t2.join();

    cout << "All transactions completed." << endl;
    return 0;
}