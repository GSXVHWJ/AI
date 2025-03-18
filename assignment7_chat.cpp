#include <iostream>
using namespace std;

class BankersAlgorithm {
private:
    int processes; // Number of processes
    int resources; // Number of resource types
    int **max;      // Maximum resource matrix
    int **allocation; // Allocation matrix
    int *available;   // Available resources
    int **need;       // Need matrix

public:
    BankersAlgorithm(int p, int r) : processes(p), resources(r) {
        // Allocate memory for matrices
        max = new int *[processes];
        allocation = new int *[processes];
        need = new int *[processes];
        for (int i = 0; i < processes; i++) {
            max[i] = new int[resources];
            allocation[i] = new int[resources];
            need[i] = new int[resources];
        }
        available = new int[resources];
    }

    ~BankersAlgorithm() {
        // Free allocated memory
        for (int i = 0; i < processes; i++) {
            delete[] max[i];
            delete[] allocation[i];
            delete[] need[i];
        }
        delete[] max;
        delete[] allocation;
        delete[] need;
        delete[] available;
    }

    void inputMatrices() {
        cout << "Enter the maximum resource matrix:\n";
        for (int i = 0; i < processes; i++) {
            cout << "P" << i << ": ";
            for (int j = 0; j < resources; j++) {
                cin >> max[i][j];
            }
        }

        cout << "Enter the allocation matrix:\n";
        for (int i = 0; i < processes; i++) {
            cout << "P" << i << ": ";
            for (int j = 0; j < resources; j++) {
                cin >> allocation[i][j];
                // Calculate the need matrix
                need[i][j] = max[i][j] - allocation[i][j];
                if (need[i][j] < 0) {
                    cout << "Error: Allocation exceeds maximum for P" << i << "!\n";
                    exit(1);
                }
            }
        }

        cout << "Enter the available resources: ";
        for (int j = 0; j < resources; j++) {
            cin >> available[j];
        }
    }

    bool isSafe() {
        bool *finish = new bool[processes]{false};
        int *work = new int[resources];
        for (int j = 0; j < resources; j++) {
            work[j] = available[j];
        }

        int *safeSequence = new int[processes];
        int count = 0;

        while (count < processes) {
            bool found = false;
            for (int p = 0; p < processes; p++) {
                if (!finish[p]) {
                    bool canAllocate = true;
                    for (int j = 0; j < resources; j++) {
                        if (need[p][j] > work[j]) {
                            canAllocate = false;
                            break;
                        }
                    }

                    
                    if (canAllocate) {
                        for (int j = 0; j < resources; j++) {
                            work[j] += allocation[p][j];
                        }
                        safeSequence[count++] = p;
                        finish[p] = true;
                        found = true;
                    }
                }
            }
            if (!found) break;
        }

        if (count == processes) {
            cout << "System is in a safe state.\nSafe sequence: ";
            for (int i = 0; i < processes; i++) {
                cout << "P" << safeSequence[i] << " ";
            }
            cout << endl;
            delete[] finish;
            delete[] work;
            delete[] safeSequence;
            return true;
        } else {
            cout << "System is not in a safe state.\n";
            delete[] finish;
            delete[] work;
            delete[] safeSequence;
            return false;
        }
    }
};

int main() {
    int p, r;
    cout << "Enter the number of processes and resources: ";
    cin >> p >> r;

    BankersAlgorithm bank(p, r);
    bank.inputMatrices();
    bank.isSafe();

    return 0;
}
