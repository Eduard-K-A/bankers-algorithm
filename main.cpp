#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits> // For numeric_limits
#include <numeric> // For iota
using namespace std;

struct Process {
    string id;
    int maxNeed;
    int holding;
    int need;
};

// Function to validate user input for integers
int getValidatedInput(const string& prompt, int minValue, int maxValue) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value < minValue || value > maxValue) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between " << minValue << " and " << maxValue << ".\n";
        } else {
            break;
        }
    }
    return value;
}

// Function to check if a given sequence of processes is safe
bool isSafeSequence(vector<Process>& processes, int totalResources, vector<int>& sequence) {
    int n = processes.size();
    int available = totalResources;
    vector<bool> finished(n, false);

    // Calculate initial available resources
    for (const auto& process : processes) {
        available -= process.holding;
    }

    // Try to execute processes in the given sequence
    for (int processIdx : sequence) {
        if (processes[processIdx].need <= available) {
            available += processes[processIdx].holding;
            finished[processIdx] = true;
        } else {
            return false;
        }
    }

    return true;
}

// Function to generate all permutations and check if each is safe
void generatePermutations(vector<Process>& processes, int totalResources) {
    int n = processes.size();
    vector<int> indices(n);
    iota(indices.begin(), indices.end(), 0); // Initialize indices array

    cout << "\nPossible combinations of processes:\n";

    do {
        for (int i = 0; i < n; i++) {
            cout << processes[indices[i]].id;
            if (i < n - 1) cout << " ";
        }

        if (isSafeSequence(processes, totalResources, indices)) {
            cout << " - SAFE\n";
        } else {
            cout << " - UNSAFE\n";
        }

    } while (next_permutation(indices.begin(), indices.end()));
}

// Function to input process details
void inputProcessDetails(vector<Process>& processes) {
    for (auto& process : processes) {
        cout << "Enter process ID: ";
        cin >> process.id;
        process.maxNeed = getValidatedInput("Enter maximum need of " + process.id + ": ", 1, 1000);
        process.holding = getValidatedInput("Enter currently holding resources of " + process.id + ": ", 0, process.maxNeed);
        process.need = process.maxNeed - process.holding;
    }
}

int main() {
    int totalResources = getValidatedInput("Enter the total resources: ", 1, 1000);
    int numProcesses = getValidatedInput("Enter the number of processes (3-10): ", 3, 10);

    vector<Process> processes(numProcesses);
    inputProcessDetails(processes);

    generatePermutations(processes, totalResources);

    return 0;
}