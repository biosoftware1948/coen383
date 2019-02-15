# include "Page.h"

static unsigned _globalIdCounter = 0;

Page::Page(unsigned parentId, unsigned localId)
        : _parentId(parentId), _localId(localId), _globalId(_globalIdCounter++) {
}
