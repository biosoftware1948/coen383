# include <random>
# include <stdlib.h>
# include <time.h>
# include "Process.h"

extern const unsigned RUN_TIME;
static unsigned idCounter = 0;

Process::Process() : _processId(idCounter++) {
    _arrivalTime = rand() % RUN_TIME;
    _serviceDuration = (rand() % 5 + 1) * 1000;
    allocatePages();
}

void Process::allocatePages() {
    unsigned numJobs = rand() % 4;
    if (numJobs == 0) numJobs = 5;
    else if (numJobs == 1) numJobs = 11;
    else if (numJobs == 2) numJobs = 17;
    else if (numJobs == 3) numJobs = 31;

    for (int i = 0; i < numJobs; i++)
        _pages.push_back(new Page(_processId));
}

unsigned Process::getArrivalTime() const {
    return _arrivalTime;
}

Page *Process::getNextPage() {
    unsigned branch = rand() % 10 + 1, delta_i;

    // get local page id
    if (branch <= 7) {
        delta_i = rand() % 2;
        if (delta_i == 0) delta_i = -1;
    } else delta_i = rand() % getNumPages();

    // keeping track of page's local id
    if (_lastReferencedPage == -1) _lastReferencedPage = 0;
    else _lastReferencedPage = (_lastReferencedPage + delta_i) % getNumPages();
    
    // return global page id
    return _pages[_lastReferencedPage];
}

bool Process::isCompleted() const {
    return _serviceDuration == _timeRun;
}

void Process::service(unsigned quantum) {
    _serviceDuration += quantum;
}

bool Process::CompareArrivalTime(const Process *left, const Process *right) {
    return left->getArrivalTime() < right->getArrivalTime();
}

