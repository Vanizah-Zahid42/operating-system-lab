#include <iostream>
#include <vector>
#include <string>
using namespace std;
struct Process { string id; int arrival, burst, completion, turnaround, waiting; bool done; };
int main() {
    vector<Process> p={{"P1",0,6,0,0,0,false},{"P2",0,8,0,0,0,false},{"P3",0,2,0,0,0,false}};
    int time=0, completed=0; double total=0;
    cout<<"Execution Order: ";
    while(completed<(int)p.size()) {
        int best=-1;
        for(int i=0;i<(int)p.size();++i)
            if(!p[i].done && p[i].arrival<=time && (best==-1 || p[i].burst<p[best].burst)) best=i;
        if(best==-1){++time;continue;}
        Process &x=p[best]; cout<<x.id<<" ";
        x.completion=time+x.burst; x.turnaround=x.completion-x.arrival;
        x.waiting=x.turnaround-x.burst; time=x.completion; x.done=true;
        total+=x.waiting; ++completed;
    }
    cout<<"\nPID Burst Waiting Turnaround\n";
    for(size_t i=0;i<p.size();++i) cout<<p[i].id<<" "<<p[i].burst<<" "<<p[i].waiting<<" "<<p[i].turnaround<<"\n";
    cout<<"Average Waiting Time: "<<total/p.size()<<" ms\n";
}
