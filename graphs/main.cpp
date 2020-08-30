#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "graph.h"

bool compare_by_size(connected_components_t a, connected_components_t b) { return a.vertices.size() > b.vertices.size(); };

int main(int, char**) {
    std::string str;
    std::ifstream file;

    file.open("data.txt");
    int i = -1, edge_pos = -1, label_pos = -1;
    std::string label;

    bool direct_graph = true;

    Graph g(direct_graph);
    while (std::getline(file, str) && !str.empty()) {
        i = str.find(" ");
        label = str.substr(0, i);
        label_pos = stoi(label) - 1;
        edge_pos = stoi(str.substr(i+1, str.size())) - 1;

        if (label_pos >= g.get_vertices().size())
            g.insert(label_pos, vertex{label});
        g.add_edge(label_pos, edge_pos);
    }
    file.close();

    std::cout << "Graph loaded, size V=" << g.get_vertices().size() << std::endl;
    std::cout << "Running Kosaraju" << std::endl;
    std::vector<connected_components_t> ccks = g.kosaraju_cc();
    std::cout << "Found " << ccks.size() << " strongly connected components" << std::endl;

    std::sort(ccks.begin(), ccks.end(), compare_by_size);
    int top = (ccks.size() > 5) ? 5 : ccks.size();
    std::cout << "SCC sizes: ";
    for (int i = 0; i < top; i++) {
        std::cout << ccks[i].vertices.size() << ",";
    }
    //434821,968,459,313,211
}

void dijkstra() {
    std::string str;
    std::ifstream file;

    file.open("dijkstraData.txt");
    int i = 0, last_i = 0, edge_pos = -1, label_pos = -1, weight = -1, comma_pos;
    std::string label, edge_and_weight;

    bool direct_graph = false;
    Graph g(direct_graph, 200);

    while (std::getline(file, str) && !str.empty()) {

        last_i = 0;
        std::cout << "Vertex: ";

        while ((i = str.find('\t', last_i)) > 0) {
            if (last_i == 0) {
                label = str.substr(last_i, i - last_i);
                label_pos = stoi(label) - 1;
                std::cout << label;
                g.insert(label_pos, vertex{label});
            } else {
                edge_and_weight = str.substr(last_i, i - last_i);
                comma_pos = edge_and_weight.find(",", 0);
                edge_pos = stoi(edge_and_weight.substr(0, comma_pos)) - 1;
                weight = stoi(edge_and_weight.substr(comma_pos+1, edge_and_weight.size()));
                std::cout << ", edge:" << edge_pos + 1 << "|weight: " << weight;
                g.add_edge(label_pos, edge_pos);
                g.add_edge_distance(label_pos, edge_pos, weight);
            }
            last_i = i+1;
            //g.add_edge(label_pos, edge_pos);
        }
        std::cout << std::endl;
    }
    file.close();

    std::cout << "Graph loaded, size V=" << g.get_vertices().size() << std::endl;
    std::vector<int> shortest_paths = g.dijkstra();
    std::vector<int> question_labels{7,37,59,82,99,115,133,165,188,197};
    //std::vector<int> question_labels{1,2,3,4,5,6,7,8};
    std::cout << "labels shortest distances: ";
    for (auto& label: question_labels) {
        std::cout << shortest_paths[label-1] << ",";
    }
    //3985,5556,4440,5377,4504,3406,2768,4731,4854,1724
}


int main(int, char**) {
    dijkstra();
    return 0;
}
