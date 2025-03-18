#include <iostream>
#include <iomanip>
#include <algorithm>
#include <climits>

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
}


void calculateSJFPreemptive(process processes[],int n){
    int Time = 0 , completed =0 ;

    while(completed<n){
       int shortestIndex = -1 ; 
       for(int i = 0 ; i<n;i++){
        if(processes[i].arrivalTime <= Time && processes[i].remainingTime >0){
            if(shortestIndex == -1 || processes[i].brustTime < processes[shortestIndex].brustTime){
                shortestIndex = i;
            }
        }
       }

       if(shortestIndex == -1){
        Time++;
        continue;
       }
       processes[shortestIndex].waitingTime = Time - processes[shortestIndex].arrivalTime;
       currentTime = processes[shortestIndex].arrivalTime + processes[shortestIndex].brustTime;
       processes[shortestIndex].remainingTime = 0;
       processes[shortestIndex].turnaroundTime = processes[shortestIndex].waitingTime + processes[shortestIndex].brustTime;
       completed++;
    }
}
void printResults() {
        double totalWaitingTime = 0;
        cout << "\nProcess ID\tArrival Time\tBurst Time\tWaiting Time\n";
        for (int i = 0; i < n; i++) {
            cout << processes[i].id << "\t\t" << processes[i].arrivalTime << "\t\t" << processes[i].burstTime << "\t\t" << processes[i].waitingTime << "\n";
            totalWaitingTime += processes[i].waitingTime;
        }
        cout << "Average Waiting Time: " << (totalWaitingTime / n) << "\n";
    };

   
int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    schedular scheduler(n);
    
     scheduler.calculateSJFPreemptive();
     printResults();

     
scheduler.printResults();
    return 0;

}