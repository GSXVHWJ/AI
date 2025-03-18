#include <iostream>
using namespace std;

class Process {
public:
    int id;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int remainingTime; 

    Process() : id(0), arrivalTime(0), burstTime(0), waitingTime(0), remainingTime(0) {}
};

class Scheduler {
private:
    Process processes[100]; 
    int n;

public:
    Scheduler(int num) : n(num) {
        for (int i = 0; i < n; i++) {
            processes[i].id = i + 1;
            cout << "Enter arrival time and burst time for process " << (i + 1) << ": ";
            cin >> processes[i].arrivalTime >> processes[i].burstTime;
            processes[i].remainingTime = processes[i].burstTime; 
            processes[i].waitingTime = 0; 
        }
    }

    void calculateFCFS() {
        int completionTime[100];
        completionTime[0] = processes[0].arrivalTime + processes[0].burstTime;
        processes[0].waitingTime = 0;

        for (int i = 1; i < n; i++) {
            completionTime[i] = max(completionTime[i - 1], processes[i].arrivalTime) + processes[i].burstTime;
            processes[i].waitingTime = completionTime[i - 1] - processes[i].arrivalTime;
        }
    }

    void calculateSJFNonPreemptive() {
        sort(processes, processes + n, [](const Process &a, const Process &b) {
            return a.arrivalTime < b.arrivalTime;
        });

        int currentTime = 0;
        for (int i = 0; i < n; i++) {
            int idx = -1;
            for (int j = 0; j < n; j++) {
                if (processes[j].arrivalTime <= currentTime && (idx == -1 || processes[j].burstTime < processes[idx].burstTime)) {
                    idx = j;
                }
            }

            if (idx != -1) {
                currentTime = max(currentTime, processes[idx].arrivalTime);
                processes[idx].waitingTime = currentTime - processes[idx].arrivalTime;
                currentTime += processes[idx].burstTime;
            }
        }
    }

    void calculateSJFPreemptive() {
        int currentTime = 0;
        bool isCompleted[100] = { false };
        int completed = 0;

        while (completed < n) {
            int idx = -1;
            for (int j = 0; j < n; j++) {
                if (!isCompleted[j] && processes[j].arrivalTime <= currentTime) {
                    if (idx == -1 || processes[j].remainingTime < processes[idx].remainingTime) {
                        idx = j;
                    }
                }
            }

            if (idx != -1) {
                processes[idx].remainingTime--;
                if (processes[idx].remainingTime == 0) {
                    isCompleted[idx] = true;
                    completed++;
                    processes[idx].waitingTime = currentTime + 1 - processes[idx].arrivalTime - processes[idx].burstTime;
                }
            }
            currentTime++;
        }
    }

    void printResults() {
        double totalWaitingTime = 0;
        cout << "\nProcess ID\tArrival Time\tBurst Time\tWaiting Time\n";
        for (int i = 0; i < n; i++) {
            cout << processes[i].id << "\t\t" << processes[i].arrivalTime << "\t\t" << processes[i].burstTime << "\t\t" << processes[i].waitingTime << "\n";
            totalWaitingTime += processes[i].waitingTime;
        }
        cout << "Average Waiting Time: " << fixed << setprecision(2) << (totalWaitingTime / n) << "\n";
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
            break;
        case 2:
            scheduler.calculateSJFNonPreemptive();
            break;
        case 3:
            scheduler.calculateSJFPreemptive();
            break;
        default:
            cout << "Invalid choice!\n";
            return 1;
    }

    scheduler.printResults();
    return 0;
}