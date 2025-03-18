#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
    int remainingTime;
};

void calculateFCFS(Process processes[], int n) {
    int currentTime = 0;
    for (int i = 0; i < n; i++) {
        processes[i].waitingTime = max(0, currentTime - processes[i].arrivalTime);
        currentTime = max(currentTime, processes[i].arrivalTime) + processes[i].burstTime;
        processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;
    }
}

void calculateSJFNonPreemptive(Process processes[], int n) {
    int currentTime = 0, completed = 0;

    while (completed < n) {
        int shortestIndex = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                if (shortestIndex == -1 || processes[i].burstTime < processes[shortestIndex].burstTime) {
                    shortestIndex = i;
                }
            }
        }
        if (shortestIndex == -1) {
            currentTime++;
            continue;
        }
        processes[shortestIndex].waitingTime = max(0, currentTime - processes[shortestIndex].arrivalTime);
        currentTime += processes[shortestIndex].burstTime;
        processes[shortestIndex].remainingTime = 0;
        processes[shortestIndex].turnaroundTime = processes[shortestIndex].waitingTime + processes[shortestIndex].burstTime;
        completed++;
    }
}

void calculateSJFPreemptive(Process processes[], int n) {
    int currentTime = 0, completed = 0;

    while (completed < n) {
        int shortestIndex = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                if (shortestIndex == -1 || processes[i].remainingTime < processes[shortestIndex].remainingTime) {
                    shortestIndex = i;
                }
            }
        }
        if (shortestIndex == -1) {
            currentTime++;
            continue;
        }
        processes[shortestIndex].remainingTime--;
        if (processes[shortestIndex].remainingTime == 0) {
            completed++;
            processes[shortestIndex].turnaroundTime = currentTime + 1 - processes[shortestIndex].arrivalTime;
            processes[shortestIndex].waitingTime = processes[shortestIndex].turnaroundTime - processes[shortestIndex].burstTime;
        }
        currentTime++;
    }
}

void displayResults(Process processes[], int n) {
    double totalWaitingTime = 0, totalTurnaroundTime = 0;

    cout << "\nProcess\tArrival\tBurst\tWaiting\tTurnaround\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << processes[i].id << "\t" << processes[i].arrivalTime << "\t"
             << processes[i].burstTime << "\t" << processes[i].waitingTime << "\t"
             << processes[i].turnaroundTime << "\n";
        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }
    cout << fixed << setprecision(2);
    cout << "Average Waiting Time: " << totalWaitingTime / n << "\n";
    cout << "Average Turnaround Time: " << totalTurnaroundTime / n << "\n";
}

int main() {
    int n, choice;
    cout << "Enter number of processes: ";
    cin >> n;

    Process processes[n];
    for (int i = 0; i < n; i++) {
        cout << "Enter arrival time and burst time for process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime >> processes[i].burstTime;
        processes[i].id = i + 1;
        processes[i].remainingTime = processes[i].burstTime;
    }

    cout << "Select Scheduling Algorithm:\n";
    cout << "1. FCFS\n2. SJF (Non-Preemptive)\n3. SJF (Preemptive)\n";
    cin >> choice;

    if (choice == 1) {
        sort(processes, processes + n, [](Process a, Process b) {
            return a.arrivalTime < b.arrivalTime;
        });
        calculateFCFS(processes, n);
    } else if (choice == 2) {
        sort(processes, processes + n, [](Process a, Process b) {
            return a.arrivalTime < b.arrivalTime;
        });
        calculateSJFNonPreemptive(processes, n);
    } else if (choice == 3) {
        calculateSJFPreemptive(processes, n);
    } else {
        cout << "Invalid choice!";
        return 1;
    }

    displayResults(processes, n);
    return 0;
}
