# include <algorithm>
# include "CPU.h"
# include "Process.h"

extern const unsigned JOB_COUNT;

//TODO: Waiting for Email response from Dr. Ezzat on CPU job scheduling

CPU::CPU() {
    for (int i = 0; i < JOB_COUNT; i++) 
        _queuedJobs.push_back(new Process());

    // sort queued jobs by arrival time
    std::sort(_queuedJobs.begin(), _queuedJobs.end(), Process::CompareArrivalTime);
}

void CPU::removeFinished() {
    for (unsigned i = 0; i < _runningJobs.size();) {
        if (_runningJobs[i]->isCompleted()) {
            _runningJobs.erase(_runningJobs.begin() + i);
            _atJobCapacity = false;
            return; 
        }
    }
}

void CPU::checkQueue() {
    
}

unsigned CPU::runIdle() {
    _clockTime += 100;

    checkQueue();
}

unsigned CPU::runProcess(unsigned processId, unsigned pageId) {
}

