#include<iostream>
#include<algorithm>
#include <queue>

using namespace std;

struct process{
    string pcs;
    int burst;
    int arival;
    int pty;
    bool sts= true;

   /* bool operator<(const process &o) const
    {
        return pty > o.pty; // jar pty kom se upore
    }*/

};

struct pcomp
{
    bool operator()(const process &a, const process &b)
    {
        return a.pty>b.pty ;
    }
};


struct bcomp
{
    bool operator()(const process &a, const process &b)
    {
        return a.burst>b.burst;
    }
};


int time,n;

bool acompare(process lhs, process rhs) { return lhs.arival < rhs.arival; }
bool bcompare(process lhs, process rhs) { return lhs.burst < rhs.burst; }


void fifo(process *pro){
    cout<<"welcome to first in first out:\nEnter processes, arrival time , burst time: "<<endl;

    for(int i=0;i<n;i++){
        cin>>pro[i].pcs>>pro[i].arival>>pro[i].burst;
    }

    sort(pro,pro+n,acompare);

    for(int i=0;i<n;i++){
        cout<<" "<<pro[i].pcs;
    }

    cout<<endl;
}

void priority(process *pro){
    cout<<"welcome to priority scheduling:\nEnter processes, arrival time , burst time, priority: "<<endl;

    for(int i=0;i<n;i++){
        cin>>pro[i].pcs>>pro[i].arival>>pro[i].burst>>pro[i].pty;
    }

    sort(pro,pro+n,acompare);

    priority_queue<process,vector<process>,pcomp> mQ;

    for(int i=0;i<n;i++){

        if(i==0){
            time=pro[i].arival;
            pro[i].burst=pro[i].burst-(pro[i+1].arival-time);

            if(pro[i].burst<=0)
                cout<<" "<<pro[i].pcs;
            else
                mQ.push(pro[i]);
        }

        else if(i==(n-1)){

            if(mQ.empty()){
                mQ.push(pro[i]);
                break;
            }


             if(pro[i].pty>mQ.top().pty){
                     mQ.push(pro[i]);
             }

             else{

                while(pro[i].pty<mQ.top().pty){
                    time=pro[i].arival;
                    process temp=mQ.top();
                    mQ.pop();

                    if(mQ.empty()){
                        temp.burst=temp.burst-(time-pro[i-1].arival);

                        if(temp.burst<=0){
                            cout<<" "<<temp.pcs;
                            mQ.push(pro[i]);
                            break;
                        }
                        else{
                            mQ.push(temp);
                            mQ.push(pro[i]);
                            break;
                        }

                    }

                    else{

                        int tt=temp.burst;
                        temp.burst=temp.burst-(time-pro[i-1].arival);
                        if(temp.burst<=0){
                            cout<<" "<<temp.pcs;
                            pro[i].arival=pro[i].arival-tt;
                        }

                        else{
                            mQ.push(temp);
                            mQ.push(pro[i]);
                            break;
                        }

                        /*if(mQ.empty()){
                            mQ.push(temp);
                            break;
                        }*/
                   }



                }
             }
        }

        else{
            if(mQ.empty()){
                mQ.push(pro[i]);
            }
            else if(pro[i].pty<mQ.top().pty&&(mQ.top().burst-(pro[i].arival-mQ.top().arival))>0){

                time=pro[i].arival;
                pro[i].burst=pro[i].burst-(pro[i+1].arival-time);
                if(pro[i].burst<=0)
                    cout<<" "<<pro[i].pcs;
                else
                    mQ.push(pro[i]);
            }
            else{
                time=pro[i].arival;
                process temp=mQ.top();
                mQ.pop();
                temp.burst=temp.burst-(pro[i+1].arival-time);
                if(temp.burst<=0){
                    cout<<" "<<temp.pcs;

                }
                else{
                    mQ.push(temp);

                }
                mQ.push(pro[i]);
            }
        }
    }

    while (!mQ.empty())
    {
        cout << " " << mQ.top().pcs;//<<"="<<mQ.top().burst<<endl;
        mQ.pop();
    }


}

void sjf(process *pro){
    cout<<"welcome to Shortest job  scheduling:\nEnter processes, arrival time , burst time: "<<endl;

    for(int i=0;i<n;i++){
        cin>>pro[i].pcs>>pro[i].arival>>pro[i].burst;
    }

    sort(pro,pro+n,bcompare);
    int timeLimit = pro[n-1].burst;

    sort(pro,pro+n,acompare);
    timeLimit =timeLimit + pro[n-1].arival;



    priority_queue<process,vector<process>,bcomp> mQ;

   // cout<<timeLimit<<endl;

    int limit=0;

    for(int i=1;i<=1000;i++){

        for(int k=0;k<n;k++){
            if(pro[k].arival==i&&pro[k].sts){
                mQ.push(pro[k]);
                pro[k].sts=false;
            }
        }

        if(!mQ.empty()){
            process temp = mQ.top();
            mQ.pop();
            temp.burst--;
            mQ.push(temp);
        }

        if(mQ.top().burst==0){
            cout<<" "<<mQ.top().pcs;
            mQ.pop();
            limit++;
        }

        if(limit==n)
            break;
    }


}

void rr(process *pro){
    cout<<"welcome to Round Robin  scheduling:\nEnter processes, arrival time , burst time: "<<endl;

    for(int i=0;i<n;i++){
        cin>>pro[i].pcs>>pro[i].arival>>pro[i].burst;
    }

    sort(pro,pro+n,acompare);

    queue<process> mQ;
    int qTrack=0;
    int limit=0;

    for(int i=1;i<=1000;i++){

        for(int k=0;k<n;k++){
            if(pro[k].arival==i&&pro[k].sts){
                mQ.push(pro[k]);
                qTrack++;
                pro[k].sts=false;
            }
        }

        for(int j=0;j<qTrack;j++){
            process temp=mQ.front();
            mQ.pop();
            temp.burst=temp.burst-4;
            mQ.push(temp);
        }

        for(int j=0;j<qTrack;j++){
            process temp=mQ.front();
            mQ.pop();
            if(temp.burst<=0){
                cout<<" "<<temp.pcs;
                qTrack--;
                limit++;

            }
            else{
                mQ.push(temp);
            }
        }

        if(limit==n)
            break;

    }

}

int main(){
    time=0;

    cout<<"enter number of process :"<<endl;

    cin>>n;
    process *pro;
    pro = new process[n];

    //fifo(pro);
    //priority(pro);
    //sjf(pro);
    //rr(pro);

    /*

    to run this code please use only one function at a time

    */

    return 0;
}
