#include <iostream>
#include <thread>
#include <vector>
using namespace std;
int main() {
    int matrix[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    int vec[3] = {1,2,3}, result[3] = {0,0,0};
    vector<thread> workers;
    for (int r=0; r<3; ++r) {
        workers.push_back(thread([&, r]() {
            for (int c=0; c<3; ++c) result[r] += matrix[r][c] * vec[c];
        }));
    }
    for (size_t i=0; i<workers.size(); ++i) workers[i].join();
    cout << "Result Vector: [" << result[0] << ", " << result[1] << ", " << result[2] << "]" << endl;
}
