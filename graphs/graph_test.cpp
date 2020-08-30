#include <iostream>
#include "graph.h"
#include <cassert>

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

void test_undirect_graph() {
    bool direct_graph = false;
    Graph graph(direct_graph);
    graph.add_vertex(vertex{"s"}); //0
    graph.add_vertex(vertex{"a"}); //1
    graph.add_vertex(vertex{"b"}); //2
    graph.add_vertex(vertex{"c"}); //3
    graph.add_vertex(vertex{"d"}); //4
    graph.add_vertex(vertex{"e"}); //5
    graph.add_edge(0, 1);
    graph.add_edge(0, 2);
    graph.add_edge(1, 3);
    graph.add_edge(2, 3);
    graph.add_edge(2, 4);
    graph.add_edge(3, 5);
    graph.add_edge(4, 5);

    test_bfs_distance(graph);
    test_dfs_distance(graph);

    test_ucc(graph);
    Graph graph2(direct_graph);
    for (int i = 0; i < 10; i++) {
        graph2.add_vertex(vertex{std::to_string(i)});
    }
    graph2.add_edge(0, 2);//cc1
    graph2.add_edge(0, 4);//cc1
    graph2.add_edge(2, 4);//cc1
    graph2.add_edge(4, 6);//cc1
    graph2.add_edge(4, 8);//cc1

    graph2.add_edge(1, 3);//cc2

    graph2.add_edge(5, 7);//cc3
    graph2.add_edge(5, 9);//cc3

    assert(graph2.undirect_connected_components().size() == 3);

}

void test_topological_sort() {
    bool direct_graph = true;
    Graph g(direct_graph);
    g.add_vertex(vertex{"1"});
    g.add_vertex(vertex{"2"});
    g.add_vertex(vertex{"3"});
    g.add_vertex(vertex{"4"});
    g.add_vertex(vertex{"5"});
    g.add_vertex(vertex{"6"});
    g.add_vertex(vertex{"7"});
    g.add_vertex(vertex{"8"});
    g.add_vertex(vertex{"9"});
    g.add_vertex(vertex{"10"});
    g.add_vertex(vertex{"11"});
    g.add_edge(0,2);//1->3
    g.add_edge(2,10);//3->11
    g.add_edge(2,4);//3->5
    g.add_edge(10,5);//11->6
    g.add_edge(5,9); //6->10
    g.add_edge(9,7);//10->8
    g.add_edge(10,7);//11->8
    g.add_edge(7,5);//8->6
    g.add_edge(4,8);//5->9
    g.add_edge(4,6);//5->7
    g.add_edge(4,0);//5->1
    g.add_edge(8,7);//9->8
    g.add_edge(8,1);//9->2
    g.add_edge(8,3);//9->4
    g.add_edge(1,9);//2->10
    g.add_edge(1,3);//2->4
    g.add_edge(3,6);//4->7
    g.add_edge(6,8);//7->9

    std::vector<int> topo = g.topological_order();
    for (int i = 0; i < topo.size(); i++) {
        std::cout << i+1 << ":" << g.get_vertices()[topo[i]].label << ", ";
    }
    assert(g.get_vertices()[topo[10]].label == "4");
}

void test_reverse() {
    /*      v
          /    \
        s       t
          \    /
            w
    original: s -> v & w -> t
    reversed: t -> w & v -> s
    */
    bool direct_graph = true;
    Graph g(direct_graph);
    g.add_vertex(vertex{"s"});
    g.add_vertex(vertex{"v"});
    g.add_vertex(vertex{"w"});
    g.add_vertex(vertex{"t"});
    g.add_edge(0, 1);//s->v
    g.add_edge(0, 2);//s->w
    g.add_edge(1, 3);//v->t
    g.add_edge(2, 3);//w->t

    
    const std::vector<vertex_t>& reversed = g.reverse();

    assert(reversed[0].label == "s");
    assert(reversed[1].label == "v");
    assert(reversed[2].label == "w");
    assert(reversed[3].label == "t");

    assert(reversed[0].edges.size() == 0);
    assert(reversed[1].edges.size() == 1);
    assert(reversed[2].edges.size() == 1);
    assert(reversed[3].edges.size() == 2);
}

void test_kosaraju() {
    bool direct_graph = true;
    Graph g(direct_graph);
    g.add_vertex(vertex{"1"});
    g.add_vertex(vertex{"2"});
    g.add_vertex(vertex{"3"});
    g.add_vertex(vertex{"4"});
    g.add_vertex(vertex{"5"});
    g.add_vertex(vertex{"6"});
    g.add_vertex(vertex{"7"});
    g.add_vertex(vertex{"8"});
    g.add_vertex(vertex{"9"});
    g.add_vertex(vertex{"10"});
    g.add_vertex(vertex{"11"});
    g.add_edge(0,2);//1->3
    g.add_edge(2,10);//3->11
    g.add_edge(2,4);//3->5
    g.add_edge(10,5);//11->6
    g.add_edge(5,9); //6->10
    g.add_edge(9,7);//10->8
    g.add_edge(10,7);//11->8
    g.add_edge(7,5);//8->6
    g.add_edge(4,8);//5->9
    g.add_edge(4,6);//5->7
    g.add_edge(4,0);//5->1
    g.add_edge(8,7);//9->8
    g.add_edge(8,1);//9->2
    g.add_edge(8,3);//9->4
    g.add_edge(1,9);//2->10
    g.add_edge(1,3);//2->4
    g.add_edge(3,6);//4->7
    g.add_edge(6,8);//7->9

    std::vector<connected_components_t> cck = g.kosaraju_cc();
    std::cout << "CCK size: " << cck.size() << std::endl;
    assert(cck.size() == 4);
}

void test_dijkstra() {
    /*
        v
      / | \
    s   |   t
      \ | /
        w
    
    */
    bool direct_graph = true;
    Graph g(direct_graph);
    g.add_vertex(vertex{"s"});
    g.add_vertex(vertex{"v"});
    g.add_vertex(vertex{"w"});
    g.add_vertex(vertex{"t"}); 
    g.add_edge(0,1);//s->v
    g.add_edge_distance(0,1,1);//s -- distance 1 --> v

    g.add_edge(0,2);//s->w
    g.add_edge_distance(0,2,3);//s -- distance 3 --> w

    g.add_edge(1,2);//v->w
    g.add_edge_distance(1,2,1);//v -- distance 1 --> w

    g.add_edge(1,3);//v->t
    g.add_edge_distance(1,3,6);//v -- distance 6 --> t

    g.add_edge(2,3);//w->t
    g.add_edge_distance(2,3,3);//w -- distance 3 --> t

    const std::vector<int>& shorted_path_distances = g.dijkstra();
    for (auto& i: shorted_path_distances) {
        std::cout << i << ",";
    }
    
    assert(shorted_path_distances[3] == 5); //s -> v -> w -> t = 1 + 1 + 3 = 5
    assert(shorted_path_distances[2] == 2); //s -> v -> w = 1 + 1 = 2 and not s -- distance 3 --> w
    assert(shorted_path_distances[1] == 1);
    assert(shorted_path_distances[0] == 0);
}

void test_direct_graph() {
    test_topological_sort();
    test_reverse();
    test_kosaraju();
    test_dijkstra();
}

int main(int, char**) {
    test_direct_graph();
    test_undirect_graph();
    return 0;
}