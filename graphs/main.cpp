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
    return 0;
}
