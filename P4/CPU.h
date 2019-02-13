# ifndef CPU_H
# define CPU_H
# include <vector>
# include "Process.h"

class CPU {
    std::vector<Process *> _queuedJobs;
    std::vector<Process *> _runningJobs;

public:
    CPU();
};

# endif /* PAGE_H */
