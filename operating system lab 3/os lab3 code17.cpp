#include <iostream>
#include <vector>
#include <string>
using namespace std;
struct Process { string id; int arrival, burst, remaining, completion, waiting; };
int main() {
    vector<Process> p={{"P1",0,7,7,0,0},{"P2",1,4,4,0,0},{"P3",2,2,2,0,0}};
    int time=0, completed=0;
    cout<<"CPU timeline (one process label per time unit): ";
    while(completed<(int)p.size()) {
        int best=-1;
        for(int i=0;i<(int)p.size();++i)
            if(p[i].arrival<=time && p[i].remaining>0 &&
               (best==-1 || p[i].remaining<p[best].remaining)) best=i;
        if(best==-1){cout<<"Idle ";++time;continue;}
        cout<<p[best].id<<" ";
        --p[best].remaining; ++time;
        if(p[best].remaining==0) {
            p[best].completion=time;
            p[best].waiting=time-p[best].arrival-p[best].burst;
            ++completed;
        }
    }
    cout<<"\nPID Completion Waiting\n";
    for(size_t i=0;i<p.size();++i) cout<<p[i].id<<" "<<p[i].completion<<" "<<p[i].waiting<<"\n";
}
