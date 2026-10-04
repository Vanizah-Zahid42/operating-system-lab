#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;
struct Process { string id; int arrival, burst, remaining, completion, waiting; bool queued; };
int main() {
    vector<Process> p={{"P1",0,3,3,0,0,false},{"P2",0,2,2,0,0,false},{"P3",0,4,4,0,0,false}};
    const int quantum=2; queue<int> ready; int time=0, completed=0;
    for(int i=0;i<(int)p.size();++i) if(p[i].arrival==0){ready.push(i);p[i].queued=true;}
    cout<<"Quantum = "<<quantum<<"\nExecution: ";
    while(completed<(int)p.size()) {
        if(ready.empty()) {
            ++time;
            for(int i=0;i<(int)p.size();++i) if(!p[i].queued&&p[i].arrival<=time){ready.push(i);p[i].queued=true;}
            continue;
        }
        int i=ready.front();ready.pop();
        int run=min(quantum,p[i].remaining);
        cout<<p[i].id<<" ("<<run<<" ms) -> ";
        time+=run;p[i].remaining-=run;
        for(int j=0;j<(int)p.size();++j) if(!p[j].queued&&p[j].arrival<=time){ready.push(j);p[j].queued=true;}
        if(p[i].remaining>0) ready.push(i);
        else {p[i].completion=time;p[i].waiting=time-p[i].arrival-p[i].burst;++completed;}
    }
    cout<<"\nPID Turnaround Waiting\n";
    for(size_t i=0;i<p.size();++i) cout<<p[i].id<<" "<<p[i].completion-p[i].arrival<<" "<<p[i].waiting<<"\n";
}
