
#ifndef MIN_CUTS_VERTEX_H
#define MIN_CUTS_VERTEX_H

#include <vector>
#include <set>

struct vertex {
    int label = -1;
    std::vector<int> edges;
    std::set<int> referenced_by;
};

typedef struct vertex vertex_t;
#endif //MIN_CUTS_VERTEX_H
