#include <vector>
#include <string>

#if !defined(GRAPH_H)
#define GRAPH_H

struct vertex {
    std::string label;
    std::vector<int> edges;
    vertex(std::string _label) {
        label = _label;
    }
};
typedef vertex vertex_t;

struct connected_components {
    int id;
    std::vector<vertex_t> vertices;
};
typedef connected_components connected_components_t;


class Graph {
private:
    std::vector<vertex_t> vertices;
    bool _direct_graph = false;
public:
    /* direct:bool direct graph if true, undirect graph otherwise */
    Graph(bool direct) {
        _direct_graph = direct;
    }
    void addVertex(vertex_t v);
    void addEdge(int a_index, int b_index);
    std::vector<std::pair<vertex_t, int>> find_bfs(const int starting_index, const std::string label);
    std::vector<connected_components_t> ucc();
    std::vector<std::pair<vertex_t, int>> find_dfs(const int starting_index, const std::string label);
    std::vector<std::string> topological_sort();
    void print();
};

#endif