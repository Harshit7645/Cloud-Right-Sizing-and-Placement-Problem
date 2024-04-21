#include<bits/stdc++.h>
using namespace std;

int B;
int S;
int K;   
int m = 1;

// 1
// 3
// 2
// 1 25 2
// 2 2
// 2 1 4
// 2 2 1 2

map<int,map<int,int>>jobs_to_chunks; //Stores chunks and their deadlines for each job
struct Node
{
    //To store the <chunks,jobID> mapped in each Time slot, this can be of atmost size S
    int mid;
    map<int,set<pair<int,int>>>VMs;
    set<int>chunks_scheduled;
    int slots_scheduled;
    Node(int machine_id)
    {
        slots_scheduled = 0;
        mid = machine_id;
    }
    void PrintSchedule()
    {
        cout<<"Whole Schedule in machine : "<<mid<<endl<<endl;
        for(int i=1; i<=S; i++)
        {
            cout<<"Scheudle for VM "<<i<<" : "<<endl;
            for(auto &x: VMs)
            {
                if(!x.second.empty())
                {
                    cout<<"Time "<<x.first<<" - Chunk: "<<x.second.begin()->first<<" Job: "<<x.second.begin()->second<<endl;
                    x.second.erase(x.second.begin()); //Delete the element after writing
                }
                else
                {
                    cout<<"Time "<<x.first<<" - Free"<<endl;
                }

            }
            cout<<endl;
        }
    }
    // If we can insert a chunk ID in time slot t
    bool CanChoose(int t, int c)
    {
        // Find the lower bound of the pair with first element >= c
        auto it = VMs[t].lower_bound({c,0});
    
        // If chunk is not already present and if it VM is free
        return !(it != VMs[t].end() && it->first == c) && VMs[t].size() < S;
    }

    // Schedule a chunk of a job in this machine at timestamp t
    void schedule(int chunk, int job, int t)
    {
        chunks_scheduled.insert(chunk);
        VMs[t].insert({chunk,job});
        slots_scheduled++;
    }
};


int main()
{
    cin>>B;
    cin>>S;
    cin>>K;
    map<int,int>deadlines;
    for(int _=0; _<K; _++)
    {
        int j; cin>>j;
        int d; cin>>d;
        int nc; cin>>nc;
        deadlines[j]=d;
        for(int i=0; i<nc; i++)
        {
            int chunk_id; cin>>chunk_id;
            //Get the chunks scheduled for each job
            jobs_to_chunks[j][chunk_id]++;
        }
    }
    
    m = 1; // Start with 1 machines
    vector<Node*>v; // Store the machines scheduled

    //First fit algo: Go to every job and try to find the first machine that can fit all of its chunks. If that is not possible schedule, as much as it can in new machines

    for(auto x : jobs_to_chunks)
    {
        int job = x.first;
        for(auto & y : x.second)
        {
            int chunk = y.first;
            bool phase1 = true; // To mark the phase
            while(y.second) // Till all are scheduled
            {
                //Phase 1 see its previous machines
                int min_slots = INT_MAX;
                Node* best_fit_machine = nullptr;
                for(int i=0; i<v.size() && phase1; i++)
                {
                    int d = deadlines[job]-1;
                    // When its already mapped or we have a free space to host that chunk in a machine
                    if((v[i]->chunks_scheduled.find(chunk)!=v[i]->chunks_scheduled.end()) || (v[i]->chunks_scheduled.size() < B))
                    {
                        // Basic schedulability check
                        if(S*(d+1)-v[i]->slots_scheduled-y.second>=0)
                        {
                            while(d>=0 && y.second)
                            {
                                if(v[i]->CanChoose(d,chunk)){
                                    v[i]->schedule(chunk,job,d);
                                    y.second--; 
                                } 
                                d--;  // Go to previous timestamp as well as decrement TS left for a job
                            }
    
                        }
                    }
                }

                if(y.second==0) break;
                phase1 = false;
                //Phase 2, create new machines to finish of the slots
                Node* new_machine = new Node(m);
                m++; v.push_back(new_machine);
                int d = deadlines[job]-1;
                while(d>=0 && y.second)
                {
                    if(v.back()->CanChoose(d,chunk)){
                        v.back()->schedule(chunk,job,d);
                        y.second--; 
                    } 
                    d--;  // Go to previous timestamp as well as decrement TS left for a job
                }

            }
        }
    }
    // Print machines to chunks
    cout<<"machine_to_chunks: "<<endl;
    for(auto x: v)
    {
        cout<<"Machine "<<x->mid<<": ";
        for(auto y: x->chunks_scheduled) cout<<y<<" ";
        cout<<endl;
    }

    //Print final schedule by calling the member function
    cout<<endl;
    for(auto x : v)
    {
        x->PrintSchedule();
        cout<<endl;
    }
}
