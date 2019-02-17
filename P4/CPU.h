# ifndef CPU_H
# define CPU_H
# include <vector>
# include <queue>
# include "Memory.h"
# include "Process.h"
# include "Page.h"

enum Replacement { FIFO, LRU, LFU, MFU, RANDOM };

class CPU {
    unsigned _clockTime = 0;
    bool _atJobCapacity = false;

    std::vector<Process *> _queuedJobs; /* processes waiting to be run. */
    std::queue<Process *> _runningJobs; /* processes currently being run. */
    Memory _memory;

    /* Function pointer for one of the 5 page replacement algorithms */
    void (CPU::*requestPage)(Page *p);
    void FIFOReplacement(Page *p);
    void LRUReplacement(Page *p);
    void LFUReplacement(Page *p);
    void MFUReplacement(Page *p);
    void RandomReplacement(Page *p);

    void checkQueue();
    void printPageRequest(Page *p, Page *old);

public:
    CPU(Replacement algorithm);

    bool isProcessesComplete() {
        return _queuedJobs.empty() && _runningJobs.empty();
    }
    unsigned getClockTime() { return _clockTime; }
    Process *getNextProcess();

    void runProcess(unsigned quantum, Process *process);
};

# endif /* CPU_H */
