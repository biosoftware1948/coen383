# ifndef PAGE_H
# define PAGE_H
# include <vector>
# include <ostream>

class Page {
    unsigned _globalId, _localId, _parentId;

public:
    Page(unsigned parentId, unsigned localId);
    
    unsigned getGlobalId() { return _globalId; }
    unsigned getLocalId() { return _localId; }
    unsigned getParentId() { return _parentId; }
};

# endif /* PAGE_H */
