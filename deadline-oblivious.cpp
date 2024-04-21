#include <bits/stdc++.h>
using namespace std;

int globalB,globalS;
// Define a struct for a node representing a Node server
struct node {
    int B, S; // B: maximum number of chunks, S: Number of VMs in the server
    int lastTime = 0; // Last time the machine was used
    multiset<int> VMs; // Multiset to keep track of VMs' end times
    set<int> chunks; // Set to keep track of accessed chunks by this server
    node(int Bval, int Sval) {
        B = Bval;
        S = Sval;
        // Initialize VMs with zeros to start with their initial time as 0.
        for (int i = 0; i < S; i++) {
            VMs.insert(0);
        }
    }
};

// Define a struct for a Job
struct deadline {
    vector<pair<int, int>> chunks; // List of pairs (Chunk ID, Number of chunks accessed by this job)
    int time = 0; // Deadline time
    int totalChunks = 0; // Total number of chunks accessed for this deadline
    int lastChunkTime = 0; // Time when the last chunk is accessed
    deadline(int t) {
        time = t;
    }
};

// Function to implement the deadline oblivious algorithm
vector<node> deadlineOblivious(vector<deadline>& deadlines) {
    vector<node> ans(1, node(globalB, globalS)); 
    for (int i = 0; i < deadlines.size(); i++) {
        cout << "For Job " << i + 1 << endl << endl;
        int jobEndTime = 0; // Initialize end time for the job
        // Iterate through each chunk in the deadline
        for (int j = 0; j < deadlines[i].chunks.size(); j++) {
            int startTime = *ans[ans.size() - 1].VMs.begin();
            // If server has maximum chunks, set start time to 0
            if (ans[ans.size() - 1].chunks.size() == globalB)
                startTime = 0;
            cout << "Start Time for chunk " << deadlines[i].chunks[j].first << " is:- " << startTime << endl;
            deadlines[i].totalChunks += deadlines[i].chunks[j].second; // Update total chunks for the deadline
            // If there's space in the current machine
            if (ans[ans.size() - 1].chunks.size() < globalB) {
                auto it = ans[ans.size() - 1].VMs.begin();
                int endTime = *it + deadlines[i].chunks[j].second;
                ans[ans.size() - 1].VMs.erase(it); 
                ans[ans.size() - 1].VMs.insert(endTime); 
                cout << "End Time for chunk " << deadlines[i].chunks[j].first << " is:- " << endTime << endl;
                jobEndTime = max(jobEndTime, endTime); // Update job end time
                ans[ans.size() - 1].chunks.insert(deadlines[i].chunks[j].first); // Insert the chunk ID
            } else { // If no space in the current machine
                // This is to calculate the last time a Job's chunk is processed on CLOUD
                for (auto x : ans[ans.size() - 1].VMs) {
                    ans[ans.size() - 1].lastTime = max(ans[ans.size() - 1].lastTime, x);
                }
                // Create a new machine and insert this in our ans vector which stores all the machines and their related information
                node machine(globalB, globalS);
                machine.chunks.insert(deadlines[i].chunks[j].first);
                ans.push_back(machine); 
                auto it = ans[ans.size() - 1].VMs.begin();
                int endTime = *it + deadlines[i].chunks[j].second; 
                ans[ans.size() - 1].VMs.erase(it); 
                ans[ans.size() - 1].VMs.insert(endTime); // Insert the updated end time
                cout << "End Time for chunk " << deadlines[i].chunks[j].first << " is:- " << endTime << endl;
                jobEndTime = max(jobEndTime, endTime); // Update job end time
                ans[ans.size() - 1].chunks.insert(deadlines[i].chunks[j].first); // Insert the chunk ID
            }
            deadlines[i].lastChunkTime = max(deadlines[i].lastChunkTime, jobEndTime); // Update last chunk time
        }
        cout << endl;
    }
    return ans; // Return the scheduled machines
}

int main() {
    int k;
    cin >> globalB; // maximum number of chunks a block can store.
    cin >> globalS; // number of VMs for a node
    cin >> k; // number of jobs
    int jobID, dline, num;
    vector<deadline> deadlines; // Vector to store deadlines for all the jobs
    for (int i = 0; i < k; i++) {
        cin >> jobID >> dline >> num; 
        deadline d(dline); 
        map<int, int> countOfChunks; // Map to store chunk ID and count of chunks
        int x;
        // Input each chunk and its count
        for (int j = 0; j < num; j++) {
            cin >> x;
            countOfChunks[x]++;
        }
        // Store chunk IDs and counts in the deadline object
        for (auto chunk : countOfChunks) {
            d.chunks.push_back({chunk.first, chunk.second});
        }
        deadlines.push_back(d); // Add the deadline to the vector
    }
    cout << endl;
    // Schedule the deadlines
    vector<node> ans = deadlineOblivious(deadlines);
    int deadlinesMissed = 0;
    // Check if deadlines are missed
    for (int i = 0; i < deadlines.size(); i++) {
        cout << "Job " << i + 1 << " completed at time :- " << deadlines[i].lastChunkTime << endl;
        if (deadlines[i].lastChunkTime >= deadlines[i].time)
            deadlinesMissed++;
    }
    cout << endl;
    cout << "Total Number of Jobs whose deadlines missed:- " << deadlinesMissed << endl;
    cout << "Total number of machines used:- " << ans.size() << endl;
}
