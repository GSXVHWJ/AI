#include <iostream>
using namespace std;

struct MemoryBlock {
    int size;
    bool allocated;
};

// Display current memory blocks
void displayMemory(MemoryBlock memory[], int n) {
    cout << "Memory Blocks:\n";
    for (int i = 0; i < n; ++i) {
        cout << "Block " << i + 1 << ": Size=" << memory[i].size
             << ", Allocated=" << (memory[i].allocated ? "Yes" : "No") << endl;
    }
}

// First Fit Allocation
void firstFit(MemoryBlock memory[], int n, int requestSize) {
    for (int i = 0; i < n; ++i) {
        if (!memory[i].allocated && memory[i].size >= requestSize) {
            memory[i].allocated = true;
            cout << "Allocated " << requestSize << " to Block " << i + 1 << endl;
            return;
        }
    }
    cout << "Allocation failed: No suitable block found.\n";
}

// Best Fit Allocation
void bestFit(MemoryBlock memory[], int n, int requestSize) {
    int bestIndex = -1;
    for (int i = 0; i < n; ++i) {
        if (!memory[i].allocated && memory[i].size >= requestSize &&
            (bestIndex == -1 || memory[i].size < memory[bestIndex].size)) {
            bestIndex = i;
        }
    }

    if (bestIndex != -1) {
        memory[bestIndex].allocated = true;
        cout << "Allocated " << requestSize << " to Block " << bestIndex + 1 << endl;
    } else {
        cout << "Allocation failed: No suitable block found.\n";
    }
}

// Worst Fit Allocation
void worstFit(MemoryBlock memory[], int n, int requestSize) {
    int worstIndex = -1;
    for (int i = 0; i < n; ++i) {
        if (!memory[i].allocated && memory[i].size >= requestSize &&
            (worstIndex == -1 || memory[i].size > memory[worstIndex].size)) {
            worstIndex = i;
        }
    }

    if (worstIndex != -1) {
        memory[worstIndex].allocated = true;
        cout << "Allocated " << requestSize << " to Block " << worstIndex + 1 << endl;
    } else {
        cout << "Allocation failed: No suitable block found.\n";
    }
}

int main() {
    const int n = 5; // Number of memory blocks
    MemoryBlock memory[n] = {{100, false}, {50, false}, {200, false}, {300, false}, {150, false}};
    int choice, requestSize;

    cout << "Initial Memory Blocks:\n";
    displayMemory(memory, n);

    while (true) {
        cout << "\nChoose Allocation Strategy:\n";
        cout << "1. First Fit\n2. Best Fit\n3. Worst Fit\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 4) break;

        cout << "Enter memory size to allocate: ";
        cin >> requestSize;

        switch (choice) {
            case 1:
                firstFit(memory, n, requestSize);
                break;
            case 2:
                bestFit(memory, n, requestSize);
                break;
            case 3:
                worstFit(memory, n, requestSize);
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }

        cout << "\nUpdated Memory Blocks:\n";
        displayMemory(memory, n);
    }

    return 0;
}
