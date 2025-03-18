#include<iostream>
#include<queue>
using namespace std;

struct process{
    int id;
    int arrivalTime;
    int brustTime;
    int Priority;
    int remainingTime;
    int waitingTime;
    int turnaroundTime;

};

float calculate_avg_waiting_time( process processes[], int n){
    total_waiting_time = 0;
    for (int i=0;i<n;i++){
      total_waiting_time += processes[i].waitingTime;
    }
    cout<<"avgrage waiting time = "<<total_Waiting_time<<endl;
}


void calculate_premptive_Priority( process processes[], int n){
      int currentTime = 0 ;

       for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].arrival_time > processes[j].arrival_time || 
               (processes[i].arrival_time == processes[j].arrival_time && processes[i].priority > processes[j].priority)) {
                swap(processes[i], processes[j]);
            }
        }
    }

    for(int i= 0;i<n;i++ ){
        
    }
      }
