#include <iostream>
#include <queue>
using namespace std;

struct Process {
    int id;            
    int arrival_time;  
    int burst_time;    
    int priority;      
    int waiting_time;   
    int turnaround_time; 
    int remaining_time; 
};


float calculate_avg_waiting_time(Process processes[], int n) {
    int total_waiting_time = 0;
    for (int i = 0; i < n; i++) {
        total_waiting_time += processes[i].waiting_time;
    }
    return (float)total_waiting_time / n;
}


void non_preemptive_priority(Process processes[], int n) {
    int current_time = 0;

    
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].arrival_time > processes[j].arrival_time || 
               (processes[i].arrival_time == processes[j].arrival_time && processes[i].priority > processes[j].priority)) {
                swap(processes[i], processes[j]);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }
        current_time += processes[i].burst_time;
        processes[i].waiting_time = current_time - processes[i].arrival_time - processes[i].burst_time;
        processes[i].turnaround_time = processes[i].burst_time + processes[i].waiting_time;
    }
}


void preemptive_priority(Process processes[], int n) {
    int completed[n] = {0};
    int current_time = 0, completed_count = 0;

    while (completed_count < n) {
        int idx = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && !completed[i] && 
               (idx == -1 || processes[i].priority < processes[idx].priority)) {
                idx = i;
            }
        }

        if (idx == -1) {
            current_time++;
            continue;
        }

        processes[idx].remaining_time--;
        current_time++;

        if (processes[idx].remaining_time == 0) {
            completed[idx] = 1;
            completed_count++;
            processes[idx].turnaround_time = current_time - processes[idx].arrival_time;
            processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
        }
    }
}


void round_robin(Process processes[], int n, int quantum) {
    queue<int> q;
    bool in_queue[n] = {false};
    int current_time = 0;
    int completed = 0;

    // for(int i = 0 ; i<n ; i++){
    //     // processes[i].waiting_time =0;
    //     processes[i].remaining_time = processes[i].burst_time;
    // }

    for (int i = 0; i < n; i++) {
        if (processes[i].arrival_time == 0) {
            q.push(i);
            in_queue[i] = true;
        }
    }

    while (completed < n) {
        if (q.empty()) {
            current_time++;
            for (int i = 0; i < n; i++) {
                if (processes[i].arrival_time == current_time && !in_queue[i]) {
                    q.push(i);
                    in_queue[i] = true;
                }
            }
            continue;
        }

        int idx = q.front();
        q.pop();
        in_queue[idx] = false;

        if (processes[idx].remaining_time > quantum) {
            current_time += quantum;
            processes[idx].remaining_time -= quantum;
        } else {
            current_time += processes[idx].remaining_time;
            processes[idx].remaining_time = 0;
            processes[idx].waiting_time = current_time - processes[idx].arrival_time - processes[idx].burst_time;
            completed++;
        }

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0 && !in_queue[i]) {
                q.push(i);
                in_queue[i] = true;
            }
        }

        if (processes[idx].remaining_time > 0) {
            q.push(idx);
            in_queue[idx] = true;
        }
    }
}


void display_results(Process processes[], int n) {
    cout << "Process\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << processes[i].id << "\t" << processes[i].arrival_time << "\t\t" 
             << processes[i].burst_time << "\t\t" << processes[i].priority << "\t\t"
             << processes[i].waiting_time << "\t\t" << processes[i].turnaround_time << endl;
    }
    cout << "Average Waiting Time: " << calculate_avg_waiting_time(processes, n) << endl;
}

int main() {
    int n, quantum;
    cout << "Enter number of processes: ";
    cin >> n;

    Process processes[n];
    
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cout << "Enter Arrival Time for Process P" << i + 1 << ": ";
        cin >> processes[i].arrival_time;
        cout << "Enter Burst Time for Process P" << i + 1 << ": ";
        cin >> processes[i].burst_time;
        cout << "Enter Priority for Process P" << i + 1 << ": ";
        cin >> processes[i].priority;
        processes[i].remaining_time = processes[i].burst_time;
    }

    cout << "Select Scheduling Algorithm:\n";
    cout << "1. Non-Preemptive Priority Scheduling\n";
    cout << "2. Preemptive Priority Scheduling\n";
    cout << "3. Round Robin Scheduling\n";
    int choice;
    cin >> choice;

    switch (choice) {
        case 1:
            non_preemptive_priority(processes, n);
            display_results(processes, n);
            break;

        case 2:
            preemptive_priority(processes, n);
            display_results(processes, n);
            break;

        case 3:
            cout << "Enter Quantum Time for Round Robin: ";
            cin >> quantum;
            round_robin(processes, n, quantum);
            display_results(processes, n);
            break;

        default:
            cout << "Invalid Choice!" << endl;
            break;
    }

    return 0;
}