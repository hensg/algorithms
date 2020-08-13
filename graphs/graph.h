#include <vector>
#include <string>

#if !defined(GRAPH_H)
#define GRAPH_H

struct vertex {
    std::string label;
    std::vector<int> edges;
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
    Graph(bool direct, const int size = 0) {
        _direct_graph = direct;
        vertices.resize(size);
    }
    void add_vertex(vertex_t v);
    void insert(const int pos, vertex_t v);
    void add_edge(int a_index, int b_index);
    const std::vector<vertex_t>& get_vertices();
    std::vector<std::pair<vertex_t, int>> find_bfs(const unsigned int starting_index, const std::string label);
    std::vector<connected_components_t> undirect_connected_components();
    std::vector<std::pair<vertex_t, int>> find_dfs(const unsigned int starting_index, const std::string label);
    std::vector<int> topological_order();
    std::vector<vertex_t> reverse();
    std::vector<connected_components_t> kosaraju_cc();
    void print();
};

#endif