# include <algorithm>
# include "CPU.h"
# include "Process.h"

extern const unsigned JOB_COUNT;

CPU::CPU() {
    for (int i = 0; i < JOB_COUNT; i++) 
        _queuedJobs.push_back(new Process());

    // sort queued jobs by arrival time
    std::sort(_queuedJobs.begin(), _queuedJobs.end(), Process::CompareArrivalTime);
}
