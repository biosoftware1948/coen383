# ifndef PROCESS_H
# define PROCESS_H
# include <vector>
# include "Page.h"

class Process {
    unsigned _processId, _arrivalTime, _serviceDuration, _timeRun = 0;
    std::vector<Page *> _pages;

    void allocatePages();
public:
    Process();
    unsigned numPages() { return _pages.size(); }
    unsigned getArrivalTime() const;
    static bool CompareArrivalTime(const Process *, const Process *);
};

# endif /* PROCESS_H */
