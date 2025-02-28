#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;
//value assignment 
const int TOTAL_MEMORY_MB = 16 * 1024 * 1024;
const int PAGE_SIZE_MB = 160; 
const int TOTAL_PAGES = 100; 
const int START_MEMORY_ADDRESS = 2000; 
struct Process {
    int processId;
    int startMemoryAddress;
    int sizeInMB;
    int unusedSpace;
};










//allocating Memory
class MemoryManager {
private:
    vector<bool> memoryPages; 
    vector<Process> processes;
    int currentMemoryAddress;

public:
    MemoryManager() : memoryPages(TOTAL_PAGES, false), currentMemoryAddress(START_MEMORY_ADDRESS) {
        srand(time(0));
    }

    
    void userMemoryAllocation() {
        int processId = 1;

        while (hasFreePages()) {
            int numPages = rand() % 30 + 1; 
            int processSize = numPages * 80;

            int requiredPages = (processSize + PAGE_SIZE_MB - 1) / PAGE_SIZE_MB;
            if (!hasEnoughPages(requiredPages)) break;

            int allocatedPages = allocatePages(requiredPages);
            int allocatedMemory = allocatedPages * PAGE_SIZE_MB;
            int unusedSpace = allocatedMemory - processSize;

            
            processes.push_back({processId, currentMemoryAddress, processSize, unusedSpace});

            
            currentMemoryAddress += allocatedMemory;
            processId++;
        }
    }//check if free
    bool hasFreePages() {
        for (bool page : memoryPages) {
            if (!page) return true;
        }
        return false;
    }//check if enough is available
    bool hasEnoughPages(int required) {
        int freePages = 0;
        for (bool page : memoryPages) {
            if (!page) freePages++;
            if (freePages >= required) return true;
        }
        return false;
    }//allocate memory
    int allocatePages(int required) {
        int allocated = 0;
        for (int i = 0; i < TOTAL_PAGES && allocated < required; i++) {
            if (!memoryPages[i]) {
                memoryPages[i] = true;
                allocated++;
            }
        }
        return allocated;
    }//print out
    void printSummary() {
        cout << left << setw(12) 
             << setw(25) << "Starting Address" 
             << setw(35) << "Size MB" 
             << setw(20) << "Unused MB" << endl;
        

        for (const Process &p : processes) {
            cout << left << setw(12) << p.processId 
                 << setw(25) << p.startMemoryAddress 
                 << setw(25) << p.sizeInMB 
                 << setw(20) << p.unusedSpace << endl;
        }
    }
};






int main() {
    MemoryManager memoryManager;
    memoryManager.userMemoryAllocation();
    memoryManager.printSummary();
    return 0;
}
