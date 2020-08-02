#include "utils.h"
#include "vertex.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

void load_graph(std::string input_file_path, std::vector<vertex_t> &vertices) {
    std::ifstream stream(input_file_path);
    std::string line, col;
    int label = -1, edge = -1;
    int start_pos = 0, tab_pos = 0;
    bool first_col = true;
    while (std::getline(stream, line)) {
        start_pos = 0, tab_pos = 0;
        first_col = true;
        std::cout << "Loading line: " << line << std::endl;
        while ((tab_pos = line.find_first_of('\t', start_pos)) != -1) {
            col = line.substr(start_pos, tab_pos - start_pos);
            if (first_col) {
                first_col = !first_col;
                label = stoi(col); //1 <= label <= 200
                vertices[label-1].label = label;
            } else {
                edge = stoi(col);
                vertices[label-1].edges.push_back(edge);
                vertices[edge-1].referenced_by.insert(label);
            }
            start_pos = tab_pos+1;
        }
    }
}

void print_graph(std::vector<vertex_t> &vertices) {
    for (auto &n: vertices) {
        std::cout << "Label: " << n.label << "\t";
        std::cout << "Edges: ";
        for (auto& m: n.edges) {
            std::cout << m << ",";
        }
        /*
        std::cout << "\tref by: ";
        for (auto& e: n.referenced_by) {
            std::cout << e << ",";
        }
        */
        std::cout << std::endl;
    }
}
