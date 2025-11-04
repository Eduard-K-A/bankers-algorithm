#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Process {
    string id;
    int maxNeed;
    int holding;
    int need;
};
// This function checks if a given sequence of processes is safe or not.
// It takes a vector of Process objects, the total resources available, and a vector of indices representing the sequence of processes.
// It returns true if the sequence is safe, false otherwise.
bool isSafeSequence(vector<Process>& processes, int totalResources, vector<int>& sequence) {
    int n = processes.size();
    int available = totalResources;
    vector<bool> finished(n, false);
    
    // Calculate initial available resources
    for (int i = 0; i < n; i++) {
        available -= processes[i].holding;
    }
    
    // Try to execute processes in the given sequence
    for (int i = 0; i < n; i++) {
        int processIdx = sequence[i];
        int need = processes[processIdx].maxNeed - processes[processIdx].holding;
        
        // Check if process can be executed
        if (need <= available) {
            // Process can complete, release its resources
            available += processes[processIdx].holding;
            finished[processIdx] = true;
        } else {
            // Process cannot be executed, sequence is unsafe
            return false;
        }
    }
    
    return true;
}


/**
 Generates all permutations of a given set of processes and checks if each permutation is safe or not.
A vector of Process objects representing the processes.
The total resources available in the system.
 */

void generatePermutations(vector<Process>& processes, int totalResources) {
    int n = processes.size();
    vector<int> indices(n);
    
    // Initialize indices array (0, 1, 2, ..., n-1)
    for (int i = 0; i < n; i++) {
        indices[i] = i;
    }
    
    cout << "\nPossible combinations of process" << endl;
    
    // Generate all permutations
    do {
        // Display the sequence
        for (int i = 0; i < n; i++) {
            cout << processes[indices[i]].id;
            if (i < n - 1) cout << " ";
        }
        
        // Check if sequence is safe
        bool safe = isSafeSequence(processes, totalResources, indices);
        
        if (safe) {
            cout << " - SAFE" << endl;
        } else {
            cout << " - UNSAFE" << endl;
        }
        
    } while (next_permutation(indices.begin(), indices.end()));
}

int main() {
    int totalResources, numProcesses;
    
    // Input total resources
    cout << "Enter the total resources: ";
    cin >> totalResources;
    
    // Input number of processes with validation
    do {
        cout << "Enter the no. of process: ";
        cin >> numProcesses;
        
        if (numProcesses < 3 || numProcesses > 10) {
            cout << "Number of processes must be between 3-10. Please try again." << endl;
        }
    } while (numProcesses < 3 || numProcesses > 10);
    
    vector<Process> processes(numProcesses);
    
    // Input process details
    for (int i = 0; i < numProcesses; i++) {
        cout << "Enter process ID for Process" << (i + 1) << ": ";
        cin >> processes[i].id;
    }
    
    for (int i = 0; i < numProcesses; i++) {
        cout << "Enter maximum need of " << processes[i].id << ": ";
        cin >> processes[i].maxNeed;
    }
    
    for (int i = 0; i < numProcesses; i++) {
        cout << "Enter the currently holding of " << processes[i].id << ": ";
        cin >> processes[i].holding;
        processes[i].need = processes[i].maxNeed - processes[i].holding;
    }
    
    // Generate and check all permutations
    generatePermutations(processes, totalResources);
    
    return 0;
}