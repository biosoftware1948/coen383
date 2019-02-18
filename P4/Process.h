# ifndef PROCESS_H
# define PROCESS_H
# include <vector>
# include "Page.h"

class Process {
    unsigned _processId,
             _arrivalTime,
             _serviceDuration,
             _timeRun = 0;
    int _lastReferencedPage = -1;

    std::vector<Page *> _pages;

    void allocatePages();
public:
    Process();
    ~Process();

    unsigned getArrivalTime() const { return _arrivalTime; }
    Page *getNextPage();
    unsigned getNumPages() const { return _pages.size(); }
    unsigned getProcessId() const { return _processId; }
    unsigned getRemainingTime() const { return _serviceDuration - _timeRun; }
    unsigned getServiceTime() const { return _serviceDuration; }

    bool isCompleted() const { return _serviceDuration == _timeRun; }

    void service(unsigned quantum); // service process for specified process

    // static function used for sorting processes by arrival time
    static bool CompareArrivalTime(const Process *, const Process *);
};
# endif /* PROCESS_H */
