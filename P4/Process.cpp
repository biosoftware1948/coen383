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
        _pages.push_back(new Page(_processId, i));
}
