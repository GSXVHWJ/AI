#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

class Process {
public:
    int id;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int remainingTime;
    int startTime;
    int endTime;

    Process() : id(0), arrivalTime(0), burstTime(0), waitingTime(0), remainingTime(0), startTime(0), endTime(0) {}
};

class Scheduler {
public:
    vector<Process> processes;
    int n;  // Number of processes

    Scheduler(int num) : n(num) {
        processes.resize(n);
        for (int i = 0; i < n; i++) {
            cout << "Enter arrival time and burst time for process " << i + 1 << ": ";
            processes[i].id = i + 1;
            cin >> processes[i].arrivalTime >> processes[i].burstTime;
            processes[i].remainingTime = processes[i].burstTime;  // For preemptive algorithms
        }
    }

    void calculateFCFS() {
        vector<int> completionTime(n);
        completionTime[0] = processes[0].arrivalTime + processes[0].burstTime;
        processes[0].startTime = processes[0].arrivalTime;
        processes[0].endTime = completionTime[0];
        processes[0].waitingTime = 0;

        for (int i = 1; i < n; i++) {
            processes[i].startTime = max(completionTime[i - 1], processes[i].arrivalTime);
            completionTime[i] = processes[i].startTime + processes[i].burstTime;
            processes[i].endTime = completionTime[i];
            processes[i].waitingTime = processes[i].startTime - processes[i].arrivalTime;
        }
    }

    void printGanttChart() {
        cout << "\nGantt Chart\n";
        for (int i = 0; i < n; i++) {
            cout << "| P" << processes[i].id << " ";
        }
        cout << "|\n";

        cout << processes[0].startTime;
        for (int i = 0; i < n; i++) {
            cout << " " << setw(4) << processes[i].endTime;
        }
        cout << "\n";
    }

    void printResults() {
        cout << "\nProcess\tArrival\tBurst\tStart\tEnd\tWaiting\n";
        for (int i = 0; i < n; i++) {
            cout << "P" << processes[i].id << "\t" 
                 << processes[i].arrivalTime << "\t"
                 << processes[i].burstTime << "\t"
                 << processes[i].startTime << "\t"
                 << processes[i].endTime << "\t"
                 << processes[i].waitingTime << "\n";
        }
    }

    // Placeholder for SJF non-preemptive and preemptive methods
    void calculateSJFNonPreemptive() {
        // Implementation goes here
    }

    void calculateSJFPreemptive() {
        // Implementation goes here
    }
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    Scheduler scheduler(n);

    cout << "Select scheduling algorithm:\n1. FCFS\n2. SJF Non-Preemptive\n3. SJF Preemptive\n";
    int choice;
    cin >> choice;

    switch (choice) {
        case 1:
            scheduler.calculateFCFS();
            scheduler.printGanttChart();
            break;
        case 2:
            scheduler.calculateSJFNonPreemptive();
            // Add Gantt chart printing here if you want
            break;
        case 3:
            scheduler.calculateSJFPreemptive();
            // Add Gantt chart printing here if you want
            break;
        default:
            cout << "Invalid choice!\n";
            break;
    }

    scheduler.printResults();  // Print the results after calculation

    return 0;
}
