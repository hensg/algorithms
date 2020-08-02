#ifndef MIN_CUTS_UTILS_H
#define MIN_CUTS_UTILS_H
#include "vertex.h"
#include <string>
#include <vector>

void load_graph(std::string input_file_path, std::vector<vertex_t> &vertices);
void print_graph(std::vector<vertex_t> &vertices);

#endif
