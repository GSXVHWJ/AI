# include<iostream>
using namespace std;

struct process{
    int id;
    int brustTime;
    int arrivalTime;
    int remainingTime;
    int waitingTime;
    int turnaroundTime;
};

void calculateFCFS(process processes[],int n){
   int currentTime = 0;
   for(int i = 0 ; i<n ; i++){
    processes[i].waitingTime = max(0,currentTime - processes[i].arrivalTime);
    currentTime = max(currentTime,processes[i].arrivalTime)+processes[i].brustTime;
    processes[i].turnaroundTime = processes[i].waitingTime + processes[i].brustTime;
   }
}

void calculateSJFPreemptive(process processes[],int n){
    int currentTime = 0 , completed =0 ;

    while(completed<n){
       int shortestIndex = -1 ; 
       for(int i = 0 ; i<n;i++){
        if(processes[i].arrivalTime <= currentTime && processes[i].remainingTime >0){
            if(shortestIndex == -1 || processes[i].brustTime < processes[shortestIndex].brustTime){
                shortestIndex = i;
            }
        }
       }

       if(shortestIndex == -1){
        currentTime++;
        continue;
       }
       processes[shortestIndex].waitingTime = currentTime - processes[shortestIndex].arrivalTime;
       currentTime = processes[shortestIndex].arrivalTime + processes[shortestIndex].brustTime;
       processes[shortestIndex].remainingTime = 0;
       processes[shortestIndex].turnaroundTime = processes[shortestIndex].waitingTime + processes[shortestIndex].brustTime;
       completed++;
    }
}

void calculateSJFPreemptive(process processes[],int n){
    int currentTime = 0 , completed =0 ;

    while(completed<n){
       int shortestIndex = -1 ; 
       for(int i = 0 ; i<n;i++){
        if(processes[i].arrivalTime <= currentTime && processes[i].remainingTime >0){
            if(shortestIndex == -1 || processes[i].remainingTime < processes[shortestIndex].remainingTime){
                shortestIndex = i;
            }
        }
       }

       if(shortestIndex == -1){
        currentTime++;
        continue;
       }
       processes[i].remainingTime--;
       if(processes[shortestIndex].remainingTime = 0){
        completed++;
       processes[shortestIndex].turnaroundTime = currentTime + 1 - processes[shortestIndex].arrivalTime;
       
       processes[shortestIndex].waitingTime = processes[shortestIndex].turnaroundTime - processes[shortestIndex].brustTime;}
       currentTime++;
       
    }
}