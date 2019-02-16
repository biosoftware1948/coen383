# include <algorithm>
#include <stdlib.h>
# include "CPU.h"
# include "Process.h"

extern const unsigned JOB_COUNT;

CPU::CPU(Replacement algorithm) {
    for (int i = 0; i < JOB_COUNT; i++)
        _queuedJobs.push_back(new Process());

    // sort queued jobs by arrival time
    std::sort(_queuedJobs.begin(), _queuedJobs.end(), Process::CompareArrivalTime);

    if(algorithm == FIFO) requestPage = &CPU::FIFOReplacement;
    else if (algorithm == LRU) requestPage = &CPU::LRUReplacement;
    else if (algorithm == LFU) requestPage = &CPU::LFUReplacement;
    else if (algorithm == MFU) requestPage = &CPU::MFUReplacement;
    else if (algorithm == RANDOM) requestPage = &CPU::RandomReplacement;
}

void CPU::checkQueue() {
    if (_queuedJobs.size() == 0) return;

    Process *process = _queuedJobs[0];
    /* If we can run a job, put at end of running queue. */
    if (process->getArrivalTime() <= _clockTime
            && (_memory.getNumFreePages() >= 4 || !_atJobCapacity)
            && _runningJobs.size() < 25 /* questionably necessary. */) {
        _queuedJobs.erase(_queuedJobs.begin());
        _runningJobs.push(process);
    }

    /* Set capacity to full if there are less than 4 pages. We can safely set here
     * because we have already pulled job off queue if capacity wasn't full. */
    if (!_atJobCapacity && _memory.getNumFreePages() <= 4) {
        _atJobCapacity = true;
    }
}

Process *CPU::getNextProcess() {
    checkQueue();
    if (_memory.isEmpty()) return nullptr;

    Process *nextProcess = _runningJobs.front();
    _runningJobs.pop();
    return nextProcess;
}

void CPU::runProcess(unsigned quantum, Process *process) {
    _clockTime += quantum;
    if (process == nullptr) return;

    (this->*this->requestPage)(nullptr);
    //(requestPage)(process->getNextPage());

    process->service(quantum);
    if (!process->isCompleted()) _runningJobs.push(process);
}

/* ----- PAGE REPLACEMENT ALGORITHMS ----- */

void CPU::FIFOReplacement(Page *p) {

}

void CPU::LRUReplacement(Page *p) {

}

void CPU::LFUReplacement(Page *p) {

}

void CPU::MFUReplacement(Page *p) {

}

void CPU::RandomReplacement(Page *p) {
    if (!_memory.isFull()) {
        _memory.addPage(p);
        return;
    }

    Page *old = _memory.getPage(rand() % _memory.getNumPages());
    _memory.replacePage(old, p);
}
