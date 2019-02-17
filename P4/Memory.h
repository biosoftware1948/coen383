# ifndef MEMORY_H
# define MEMORY_H
# include <algorithm>
# include <deque>
# include "Page.h"

extern const unsigned NUM_PAGES;

class Memory {
    std::deque<Page *> _memory;

public:
    bool isEmpty() { return _memory.empty(); }
    bool isFull() { return _memory.size() >= NUM_PAGES; }

    unsigned getNumFreePages() { return NUM_PAGES - _memory.size(); }
    unsigned getNumPages() { return _memory.size(); }
    Page *getPage(unsigned index) { return _memory[index]; }

    void addPage(Page *p);
    bool contains(const Page *page) {
        return std::find(_memory.begin(), _memory.end(), page) != _memory.end();
    }
    void replacePage(Page *oldPage, Page *newPage);
    void removePage(Page *oldPage);
    void removeFirstPage() { _memory.pop_front(); }
};

# endif /* MEMORY_H */
