#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
struct Process { string id; int arrival, burst, completion, turnaround, waiting; };
int main() {
    vector<Process> p={{"P1",0,5,0,0,0},{"P2",1,3,0,0,0},{"P3",2,8,0,0,0}};
    stable_sort(p.begin(),p.end(),[](const Process& a,const Process& b){return a.arrival<b.arrival;});
    int time=0; double total=0;
    cout<<"PID Arrival Burst Completion Turnaround Waiting\n";
    for(size_t i=0;i<p.size();++i) {
        if(time<p[i].arrival) time=p[i].arrival;
        p[i].completion=time+p[i].burst;
        p[i].turnaround=p[i].completion-p[i].arrival;
        p[i].waiting=p[i].turnaround-p[i].burst;
        time=p[i].completion; total+=p[i].waiting;
        cout<<p[i].id<<" "<<p[i].arrival<<" "<<p[i].burst<<" "<<p[i].completion<<" "<<p[i].turnaround<<" "<<p[i].waiting<<"\n";
    }
    cout<<"Average Waiting Time: "<<total/p.size()<<" ms\n";
}
