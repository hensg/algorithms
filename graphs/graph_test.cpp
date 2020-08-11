#include <iostream>
#include "graph.h"

void test_bfs_distance(Graph& graph) {
    std::string label_to_find = "s";
    std::vector<std::pair<vertex, int>> found_vec = graph.find_bfs(4, label_to_find);
    assert(found_vec.size() == 1);
    assert(found_vec[0].second == 2);
}

void test_ucc(Graph& graph) {
    std::vector<connected_components_t> cc_vec = graph.undirect_connected_components();
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
    graph.addVertex(vertex{"s"}); //0
    graph.addVertex(vertex{"a"}); //1
    graph.addVertex(vertex{"b"}); //2
    graph.addVertex(vertex{"c"}); //3
    graph.addVertex(vertex{"d"}); //4
    graph.addVertex(vertex{"e"}); //5
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 3);
    graph.addEdge(2, 4);
    graph.addEdge(3, 5);
    graph.addEdge(4, 5);
    graph.print();

    test_bfs_distance(graph);
    test_dfs_distance(graph);

    test_ucc(graph);
    Graph graph2(direct_graph);
    for (int i = 0; i < 10; i++) {
        graph2.addVertex(vertex{std::to_string(i)});
    }
    graph2.addEdge(0, 2);//cc1
    graph2.addEdge(0, 4);//cc1
    graph2.addEdge(2, 4);//cc1
    graph2.addEdge(4, 6);//cc1
    graph2.addEdge(4, 8);//cc1

    graph2.addEdge(1, 3);//cc2

    graph2.addEdge(5, 7);//cc3
    graph2.addEdge(5, 9);//cc3

    assert(graph2.undirect_connected_components().size() == 3);

}

void test_topological_sort(Graph& g) {
    /*      v
          /    \
        s       t
          \    /
            w
    s -> v | w -> t  (0:s, 1:v, 2:w, 3:t)
    s -> w | v -> t  (0:s, 1:w, 2:v, 3:t)
    two possible topological orders
    */
    std::vector<int> topo = g.topological_sort();
    for (int i = 0; i < topo.size(); i++) {
        std::cout << std::to_string(i) << ":" << g.get_vertices()[topo[i]].label << ", ";
    }

    assert(g.get_vertices()[topo[0]].label == "s");
    assert(g.get_vertices()[topo[1]].label == "v");
    assert(g.get_vertices()[topo[2]].label == "w");
    assert(g.get_vertices()[topo[3]].label == "t");
}

void test_undirect_graph() {
    bool direct_graph = true;
    Graph g(direct_graph);
    g.addVertex(vertex{"s"});
    g.addVertex(vertex{"v"});
    g.addVertex(vertex{"w"});
    g.addVertex(vertex{"t"});
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