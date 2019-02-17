# include <cassert>
# include "Memory.h"
# include "Page.h"

void Memory::addPage(Page *p) {
    assert(!isFull());

    _memory.push_back(p);
}

void Memory::replacePage(Page *oldPage, Page *newPage) {
    for (unsigned i = 0; i < _memory.size(); i++)
        if (_memory[i] == oldPage)
            _memory[i] = newPage;
}

void Memory::removePage(Page *oldPage){
    for (unsigned i = 0; i < _memory.size(); i++){
        if (_memory[i] == oldPage){
            _memory.erase(_memory.begin() + i);
            return;
        }
    }
}
