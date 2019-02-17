# include <algorithm>
# include <iostream>
# include <stdlib.h>
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
    if (_runningJobs.empty()) return nullptr;

    Process *nextProcess = _runningJobs.front();
    _runningJobs.pop();
    return nextProcess;
}

void CPU::runProcess(unsigned quantum, Process *process) {
    if (process == nullptr) {
        _clockTime += quantum;
        return;
    }

    (this->*this->requestPage)(process->getNextPage());

    _clockTime += quantum;
    process->service(quantum);
    if (!process->isCompleted()) _runningJobs.push(process);
}

void CPU::printPageRequest(Page *p, Page *old) {
    std::string location =
            _memory.contains(p) ? "In Memory" : "On Disk";

    std::cout << "<" << _clockTime;
    std::cout << ",    PROC: " << p->getParentId();
    std::cout << ",\t" << "PAGE: " << p->getLocalId();
    std::cout << ",\t" << location;
    if (old != nullptr) {
        std::cout << ",\tReplacing PROC: " << old->getParentId();
        std::cout << " PAGE: " << old->getLocalId();
    }
    std::cout << ">" << std::endl;
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
    // Page to be replaced
    Page *old = nullptr;

    // Check for page hit
    if (!_memory.contains(p) && _memory.isFull())
        old = _memory.getPage(rand() % _memory.getNumPages());

    printPageRequest(p, old);

    // Page fault
    if (_memory.contains(p)) return;
    else if (!_memory.isFull()) _memory.addPage(p);
    // Page replacement required
    else _memory.replacePage(old, p);
}
