#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <set> 
using namespace std;

// Function to generate a random number between min and max
int random(int min, int max) {
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

int main(int argc, char *argv[]) {
    //enter B, S, K
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " B S K\n";
        exit(EXIT_FAILURE);
    }

    // Parse command-line arguments
    int B = stoi(argv[1]);  // Number of chunks that can be hosted in a Cloud Server
    int S = stoi(argv[2]);  // Number of VMs in a single Cloud Server
    int K = stoi(argv[3]);  // Total number of Jobs
    int N = random(B,B*3); // Total number of chunks

    // Open file for writing
    ofstream file("testcase.txt");
    if (!file) {
        cerr << "Error: Could not open the file.\n";
        return 1;
    }

    // Write parameters to the file
    file << B << endl;
    file << S << endl;
    file << K << endl;

    // Generate test case for each job
    for (int k = 1; k <= K; ++k) {
        int deadline = random(1, 25); // Deadline for job k
        int num_chunks = random(1, 1.5*N); // Number of chunks accessed by job k

        // Set to store generated chunk IDs
        vector<int> chunk_ids;

        // Generate unique chunk IDs accessed by the job
        while (chunk_ids.size() < num_chunks) {
            int chunk_id = random(1, N); // Generate chunk ID
            chunk_ids.push_back(chunk_id); // Insert chunk ID into the set
        }

        // Job ID, Deadline, Number of chunks accessed by that job
        file << k << " " << deadline << " " << num_chunks << endl;

        // Write chunk IDs accessed by the job
        for (int chunk_id : chunk_ids) {
            file << chunk_id << " ";
        }
        file << endl;
    }

    // Close the file
    file.close();

    cout << "Test case file generated successfully.\n";

    return 0;
}
