#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <ctime>
#include <cmath>
#include "utils.h"

std::vector<vertex_t> contract_graph(std::vector<vertex_t> vertices) {
  //std::cout << "Contracting graph..." << std::endl;

  std::vector<int> remaining_vertices_index;
  for (int i = 0; i < vertices.size(); i++)
    remaining_vertices_index.push_back(i);

  srand((int)time(0));
  int a = 0, b = 0, random_vertex_pos = 0;
  while (remaining_vertices_index.size() > 2) {
    do {
      random_vertex_pos = rand() % remaining_vertices_index.size();
      a = remaining_vertices_index[random_vertex_pos];
      b = vertices[a].edges[rand() % vertices[a].edges.size()] - 1; //1 <= edge <= N
    } while (a == b);
    remaining_vertices_index.erase(remaining_vertices_index.begin()+random_vertex_pos);

    //std::cout << "Contracting " << vertices[a].label << " -> " << vertices[b].label << std::endl;
    for (auto edge: vertices[a].edges) {
      if (edge != vertices[a].label && edge != vertices[b].label)
        vertices[b].edges.push_back(edge);
    }

    for (auto& ref_label: vertices[a].referenced_by) {
      vertex_t n = vertices[ref_label-1];
      int i = 0;
      while (i < n.edges.size()) {
        if (n.edges[i] == vertices[a].label) {
          n.edges.erase(n.edges.begin() + i);
          if (n.label != vertices[b].label)
            n.edges.push_back(vertices[b].label);
        } else {
          i++;
        }
      }
    }

    vertices[a].edges.clear();
    vertices[a].label = 0;
    //print_graph(vertices);
  }

  std::vector<vertex_t> contracted_graph(2);
  contracted_graph[0] = vertices[remaining_vertices_index[0]];
  contracted_graph[1] = vertices[remaining_vertices_index[1]];
  return contracted_graph;
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    int N = 200;
    //std::string input_file = "/Users/henriquegoulart/Projects/algos/graphs/min-cuts/min_cuts_short.txt";
    std::string input_file = "/Users/henriquegoulart/Projects/algos/graphs/min-cuts/min_cuts.txt";

    std::vector<vertex_t> vertices(N);
    load_graph(input_file, vertices);
    //print_graph(vertices);

    int min_cut = N;
    std::vector<vertex_t> contracted_graph;
    for (int i = 0; i < N*(N-1)/2*log(N); i++) {
      contracted_graph = contract_graph(vertices);
      if (contracted_graph[0].edges.size() < min_cut) {
        min_cut = contracted_graph[0].edges.size();
      }
    }

    std::cout << "graph contracted..." << std::endl;
    std::cout << "Min-Cut: " << min_cut;
    return 0;
}