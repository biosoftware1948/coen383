# ifndef PROCESS_H
# define PROCESS_H
# include <vector>
# include "Page.h"

class Process {
    unsigned _processId, 
             _lastReferencedPage = -1,
             _arrivalTime,
             _serviceDuration,
             _timeRun = 0;
    
    std::vector<Page *> _pages;

    void allocatePages();
public:
    Process();

    unsigned getNumPages() const { return _pages.size(); }
    unsigned getArrivalTime() const;
    Page *getNextPage();

    bool isCompleted() const;
    
    void service(unsigned quantum); // service process for specified process
    
    // static function used for sorting processes by arrival time
    static bool CompareArrivalTime(const Process *, const Process *);
}; 
# endif /* PROCESS_H */
