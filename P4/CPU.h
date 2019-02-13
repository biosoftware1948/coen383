# ifndef CPU_H
# define CPU_H
# include <vector>
# include "Process.h"
# include "Page.h"

extern const unsigned NUM_PAGES;

class CPU {
    unsigned _clockTime = 0;
    bool _atJobCapacity = false;

    std::vector<Process *> _queuedJobs;
    std::vector<Process *> _runningJobs;
    
    class Memory {
        std::vector<Page *> _memory;
    public:
        bool isFull() { return _memory.size() >= NUM_PAGES; }
    };
public:
    CPU();

    unsigned getClockTime() { return _clockTime; }

    void removeFinished();
    void checkQueue();
    unsigned runIdle(); // returns Id of next job to run.
    unsigned runProcess(unsigned processId, unsigned pageId = 0);
};

# endif /* PAGE_H */
