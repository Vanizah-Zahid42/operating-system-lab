#include <iostream>
#include <vector>
#include <string>
using namespace std;
struct Process { string id; int priority, burst, arrival, remaining, completion, waiting; };
int main() {
    vector<Process> p={{"P1",2,4,0,4,0,0},{"P2",1,3,1,3,0,0},{"P3",3,2,2,2,0,0}};
    int time=0, completed=0;
    while(completed<(int)p.size()) {
        int best=-1;
        for(int i=0;i<(int)p.size();++i)
            if(p[i].arrival<=time && p[i].remaining>0 &&
               (best==-1 || p[i].priority<p[best].priority)) best=i;
        if(best==-1){++time;continue;}
        --p[best].remaining;++time;
        if(p[best].remaining==0) {
            p[best].completion=time;
            p[best].waiting=time-p[best].arrival-p[best].burst;
            ++completed;
        }
    }
    cout<<"PID Priority Burst Arrival Waiting\n";
    for(size_t i=0;i<p.size();++i)
        cout<<p[i].id<<" "<<p[i].priority<<" "<<p[i].burst<<" "<<p[i].arrival<<" "<<p[i].waiting<<"\n";
}
