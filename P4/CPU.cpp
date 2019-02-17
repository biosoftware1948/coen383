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

// TODO: Broken - fix seg-faults and duplicated frees
CPU::~CPU() {
    // For now just allowing memory leaks
    /*while (!_runningJobs.empty()) {
        delete _runningJobs.front();
        _runningJobs.pop();
    }
    for (unsigned i = 0; i < _queuedJobs.size(); i++) delete _queuedJobs[i];
    delete this; */
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
    else delete process;
}

void CPU::printPageRequest(Page *p, Page *old) {
    std::string location = _memory.contains(p) ? "In Memory" : "On Disk";

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

    Page * old = nullptr;

    if (!_memory.contains(p) && _memory.isFull())
        old = _memory.getPage(0);

    printPageRequest(p, old);

    if (_memory.contains(p)) return; // Page hit
    else if(!_memory.isFull()) _memory.addPage(p); // Page fault
    else{
        _memory.removeFirstPage(); // remove 'first-in' page
        _memory.addPage(p); // add new page
    }

}

void CPU::LRUReplacement(Page *p) {
    Page *old = nullptr;

    if (!_memory.contains(p) && _memory.isFull())
        old = _memory.getPage(0);

    printPageRequest(p, old);

    // this can probably be cleaner
    if (_memory.contains(p)){
        _memory.removePage(p);
        _memory.addPage(p);
    } else if (!_memory.isFull()){
        _memory.addPage(p);
    } else {
        _memory.removeFirstPage();
        _memory.addPage(p);
    }
}

void CPU::LFUReplacement(Page *p) {
    Page *old = nullptr;
    //Replacement logic
    if (!_memory.contains(p) && _memory.isFull()) {
        old = _memory.getPage(0);
        for(int i = 1; i < _memory.getNumPages(); ++i) {
            if (_memory.getPage(i)->getFrequency() < old->getFrequency()) {
                  old = _memory.getPage(i);
            }
        }
#ifdef DEBUG
    printf("DEBUG: Page %d has been chosen by LFU, with frequency of %d\n", old->getLocalId(), old->getFrequency());
#endif
    }
    if (_memory.contains(p)) { //page hit
      return;
    }
    else if (!_memory.isFull()) {
      _memory.addPage(p); //space in memory
    }
    else {
      //Does this branch ever get executed? Feels like 
      //the rest of the code covers this case...
      _memory.removeFirstPage();
      _memory.addPage(p);
    }
    printPageRequest (p, old);
      
}

void CPU::MFUReplacement(Page *p) {
    Page *old = nullptr;
    //Replacement logic
    if (!_memory.contains(p) && _memory.isFull()) {
        old = _memory.getPage(0);
        for(int i = 1; i < _memory.getNumPages(); ++i) {
            if (_memory.getPage(i)->getFrequency() > old->getFrequency()) {
                  old = _memory.getPage(i);
            }
        }
#ifdef DEBUG
    printf("DEBUG: Page %d has been chosen by MFU, with frequency of %d\n", old->getLocalId(), old->getFrequency());
#endif
    }
    if (_memory.contains(p)) { //page hit
      return;
    }
    else if (!_memory.isFull()) {
      _memory.addPage(p); //space in memory
    }
    else {
      //Does this branch ever get executed? Feels like 
      //the rest of the code covers this case...
      _memory.removeFirstPage();
      _memory.addPage(p);
    }
    printPageRequest (p, old);
}

void CPU::RandomReplacement(Page *p) {
    Page *old = nullptr; // Page to be replaced

    if (!_memory.contains(p) && _memory.isFull())
        old = _memory.getPage(rand() % _memory.getNumPages());

    printPageRequest(p, old);

    if (_memory.contains(p)) return; // Page hit
    else if (!_memory.isFull()) _memory.addPage(p); // Page fault
    else _memory.replacePage(old, p); // Page replacement required
}
