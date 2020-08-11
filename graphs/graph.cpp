#include <queue>
#include <stack>
#include <vector>
#include <set>
#include <string>
#include <iostream>
#include "graph.h"

void Graph::addVertex(vertex_t v) {
    vertices.push_back(v);
};
void Graph::addEdge(int a_index, int b_index) {
    vertices[a_index].edges.push_back(b_index);
    if (!_direct_graph)
        vertices[b_index].edges.push_back(a_index);
};

const std::vector<vertex_t>& Graph::get_vertices() {
    return vertices;
};

std::vector<std::pair<vertex_t, int>> Graph::find_bfs(const unsigned int starting_index, const std::string label) {
    std::vector<std::pair<vertex_t, int>> vertices_found;
    std::set<int> explored;

    std::queue<int> q;
    q.push(starting_index);

    std::vector<int> distance(vertices.size());
    distance[starting_index] = 0;

    int i;
    while (!q.empty()) {
        i = q.front();
        if (explored.find(i) == explored.end()) {
            explored.insert(i);
            if (vertices[i].label == label) {
                vertices_found.push_back(std::pair<vertex_t,int>(vertices[i], distance[i]));
            }
            for (auto e: vertices[i].edges) {
                distance[e] = distance[i] + 1;
                q.push(e);
            }
        }
        q.pop();
    }
    return vertices_found;
}

std::vector<connected_components_t> Graph::undirect_connected_components() {
    std::vector<connected_components_t> cc_vector;

    std::vector<bool> explored(vertices.size());
    std::queue<int> q;

    int numCCs = 0;
    for (int i = 0; i < vertices.size(); i++) {
        if (!explored[i]) {
            connected_components_t cc{++numCCs};
            cc_vector.push_back(cc);
            q.push(i);

            while (!q.empty()) {
                int v = q.front();
                q.pop();
                cc.vertices.push_back(vertices[v]);
                explored[v] = true;
                for (auto& edge: vertices[v].edges) {
                    if (!explored[edge])
                        q.push(edge);
                }
            }
        }
    }
    return cc_vector;
}

std::vector<std::pair<vertex_t, int>> Graph::find_dfs(const unsigned int starting_index, const std::string label) {
    std::vector<std::pair<vertex_t, int>> vec;
    std::vector<bool> explored(vertices.size());
    std::vector<int> distance(vertices.size());

    std::stack<int> stack;
    stack.push(starting_index);
    distance[starting_index] = 0;

    while (!stack.empty()) {
        int i = stack.top();
        stack.pop();

        explored[i] = true;
        if (vertices[i].label == label)
            vec.push_back(std::pair<vertex_t, int>(vertices[i], distance[i]));

        for (auto& edge: vertices[i].edges) {
            if (!explored[edge]) {
                stack.push(edge);
                distance[edge] = distance[i] + 1;
            }
        }
    }
    return vec;
}

std::vector<int> Graph::topological_sort() {
    std::vector<int> topo_sort_vec(vertices.size());
    std::vector<int> explored(topo_sort_vec.size());
    std::stack<int> stack;

    int j, currPos = vertices.size(), numCCs = 0;

    for (int i = 0; i < vertices.size(); i++) {
        if (!explored[i]) {
            stack.push(i);
            while (!stack.empty()) {
                j = stack.top();
                if (!explored[j]) {
                    explored[j] = true;
                    for (auto& edge: vertices[j].edges) {
                        if (!explored[edge])
                            stack.push(edge);
                    }
                } else {
                    stack.pop(); //pop stack only after completely expanded a path
                    if (currPos > 0)
                        topo_sort_vec[--currPos] = j;
                }
            }
        }
    }
    return topo_sort_vec;
}

void Graph::print() {
    for (auto& v: vertices) {
        std::cout << "Vertice: " << v.label << "\tEdges: ";
        for (auto& e: v.edges) {
            std::cout << vertices[e].label << ",";
        }
        std::cout << std::endl;
    }
}
