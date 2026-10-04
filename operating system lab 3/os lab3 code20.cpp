#include <iostream>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;
struct Process { string id; int remaining; };
int main() {
    queue<Process> q1,q2,q3;
    q1.push({"P1",6}); q1.push({"P2",1});
    int time=0;
    while(!q1.empty()||!q2.empty()||!q3.empty()) {
        if(!q1.empty()) {
            Process p=q1.front();q1.pop();int run=min(2,p.remaining);
            cout<<"Time "<<time<<": "<<p.id<<" runs in Q1 for "<<run<<" ms";
            time+=run;p.remaining-=run;
            if(p.remaining>0){q2.push(p);cout<<" -> demoted to Q2\n";}else cout<<" -> finished\n";
        } else if(!q2.empty()) {
            Process p=q2.front();q2.pop();int run=min(4,p.remaining);
            cout<<"Time "<<time<<": "<<p.id<<" runs in Q2 for "<<run<<" ms";
            time+=run;p.remaining-=run;
            if(p.remaining>0){q3.push(p);cout<<" -> demoted to Q3\n";}else cout<<" -> finished\n";
        } else {
            Process p=q3.front();q3.pop();
            cout<<"Time "<<time<<": "<<p.id<<" runs in Q3 for "<<p.remaining<<" ms -> finished\n";
            time+=p.remaining;p.remaining=0;
        }
    }
    cout<<"All jobs completed. Basic MLFQ simulation; aging is not implemented."<<endl;
}
