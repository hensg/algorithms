#include <iostream>
#include "graph.h"

void test_bfs_distance(Graph& graph) {
    std::string label_to_find = "s";
    std::vector<std::pair<vertex, int>> found_vec = graph.find_bfs(4, label_to_find);
    assert(found_vec.size() == 1);
    assert(found_vec[0].second == 2);
}

void test_ucc(Graph& graph) {
    std::vector<connected_components_t> cc_vec = graph.ucc();
    assert(cc_vec.size() == 1);
}

void test_dfs_distance(Graph& graph) {
    std::string label_to_find = "s";
    std::vector<std::pair<vertex, int>> found_vec = graph.find_dfs(4, label_to_find);
    assert(found_vec.size() == 1);
    assert(found_vec[0].second == 4);
}

void test_direct_graph() {
    bool direct_graph = false;
    Graph graph(direct_graph);
    graph.addVertex(vertex("s")); //0
    graph.addVertex(vertex("a")); //1
    graph.addVertex(vertex("b")); //2
    graph.addVertex(vertex("c")); //3
    graph.addVertex(vertex("d")); //4
    graph.addVertex(vertex("e")); //5
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 3);
    graph.addEdge(2, 4);
    graph.addEdge(3, 5);
    graph.addEdge(4, 5);
    graph.print();

    test_bfs_distance(graph);
    test_ucc(graph);
    test_dfs_distance(graph);
}

void test_topological_sort(Graph& g) {
    std::vector<std::string> topo = g.topological_sort();
    std::cout << topo[0];
    assert(topo[0] == "0:s");
}

void test_undirect_graph() {
    bool direct_graph = true;
    Graph g(direct_graph);
    g.addVertex(vertex("s"));    
    g.addVertex(vertex("v"));    
    g.addVertex(vertex("w"));    
    g.addVertex(vertex("t"));    
    g.addEdge(0, 1);//s->v
    g.addEdge(0, 2);//s->w
    g.addEdge(1, 3);//v->t
    g.addEdge(2, 3);//w->t
    test_topological_sort(g);
}

int main(int, char**) {
    test_direct_graph();
    test_undirect_graph();
    return 0;
}