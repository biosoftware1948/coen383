# ifndef PAGE_H
# define PAGE_H
# include <vector>
# include <ostream>

class Page {
    unsigned _localId, _globalId, _parentId;

public:
    Page(unsigned parentId, unsigned localId);
    
    unsigned getLocalId() { return _localId; }
    unsigned getGlobalId() { return _globalId; }
};

# endif /* PAGE_H */
