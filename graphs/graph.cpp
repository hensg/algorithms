#include <queue>
#include <stack>
#include <vector>
#include <set>
#include <string>
#include <iostream>
#include "graph.h"

void Graph::add_vertex(vertex_t v) {
    vertices.push_back(v);
};
void Graph::insert(const int pos, vertex_t v) {
    if (pos >= vertices.size()) {
        vertices.resize(pos+1);
    }
    vertices[pos] = v;
};
void Graph::add_edge(int a_index, int b_index) {
    vertices[a_index].edges.push_back(b_index);
    if (!_direct_graph)
        vertices[b_index].edges.push_back(a_index);
};

const std::vector<vertex_t>& Graph::get_vertices() {
    return vertices;
};

std::vector<std::pair<vertex_t, int>> Graph::find_bfs(const unsigned int starting_index, const std::string label) {
    std::vector<std::pair<vertex_t, int>> vertices_found;
    std::vector<bool> explored(vertices.size());

    std::queue<int> q;
    q.push(starting_index);

    std::vector<int> distance(vertices.size());
    distance[starting_index] = 0;

    int i;
    while (!q.empty()) {
        i = q.front();
        if (!explored[i]) {
            explored[i] = true;
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
            cc_vector.push_back(connected_components{++numCCs});
            q.push(i);

            while (!q.empty()) {
                int v = q.front();
                q.pop();
                cc_vector[numCCs-1].vertices.push_back(vertices[v]);
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

void print_stack(std::stack<int> stack) {
    std::cout << "stack: ";
    while (!stack.empty()) {
        std::cout << stack.top() << ", ";
        stack.pop();
    }
    std::cout << std::endl;
}

std::vector<int> Graph::topological_order() {
    std::vector<int> topo_order_vec(vertices.size());
    std::vector<bool> explored(vertices.size());
    std::stack<int> stack;

    int currPos = vertices.size() - 1;

    for (int i = 0; i < vertices.size(); i++) {
        stack.push(i);
        while (!stack.empty()) {
            if (!explored[stack.top()]) {
                explored[stack.top()] = true;
                for (auto& edge: vertices[stack.top()].edges) {
                    if (!explored[edge])
                        stack.push(edge);
                }
            } else {
                if (topo_order_vec[stack.top()] == 0) {//vertex may be stacked more than once
                    topo_order_vec[stack.top()] = currPos;
                    currPos--;
                }
                stack.pop(); //pop stack only after completely expanded a path
            }
        }
    }
    std::vector<int> vector_sorted_by_topo_order(topo_order_vec.size());
    for (int i = 0; i < topo_order_vec.size(); i++) {
        vector_sorted_by_topo_order[topo_order_vec[i]] = i;
    }
    return vector_sorted_by_topo_order;
}

std::vector<vertex_t> Graph::reverse() {
    std::vector<vertex_t> reversed_vertices(vertices.size());
    for (int i = 0; i < vertices.size(); i++) {
        reversed_vertices[i] = vertex{vertices[i].label};
    }
    for (int i = 0; i < vertices.size(); i++) {
        for (auto& edge: vertices[i].edges) {
            reversed_vertices[edge].edges.push_back(i);
        }
    }
    return reversed_vertices;
};

std::vector<connected_components_t> Graph::kosaraju_cc() {
    std::vector<connected_components_t> cc_vec;

    std::vector<int> topo_sort = topological_order();
    std::vector<vertex_t> reversed = reverse();

    std::vector<bool> explored(vertices.size());
    std::stack<int> stack;

    int numCC = 0;
    for (auto& i: topo_sort) {
        if (!explored[i]) {
            numCC++;
            cc_vec.push_back(connected_components{numCC});
            stack.push(i);

            while (!stack.empty()) {
                if (!explored[stack.top()]) {
                    explored[stack.top()] = true;
                    cc_vec[numCC-1].vertices.push_back(reversed[stack.top()]);

                    for (auto& edge: reversed[stack.top()].edges) {
                        if (!explored[edge])
                            stack.push(edge);
                    }

                } else {
                    stack.pop();
                }
            }
        }
    }
    return cc_vec;
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
