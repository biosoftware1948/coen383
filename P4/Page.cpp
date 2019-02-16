# include "Page.h"

static unsigned _globalIdCounter = 0;

Page::Page(unsigned parentId)
        : _parentId(parentId), _globalId(_globalIdCounter++) {
}
