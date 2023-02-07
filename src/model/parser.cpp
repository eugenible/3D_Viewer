#include "parser.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <set>
#include <sstream>
#include <string>

#include "data.h"
#include "transformer.h"

using namespace s21;

using std::array;
using std::string;
using std::stringstream;
using std::vector;

void Parser::addVertice(Data *data, const string &line) {
  array<double, 3> coordinates;
  stringstream iss(line);
  string tok;
  size_t counter = 0;
  int iter = 0;
  while (getline(iss, tok, ' ')) {
    if (iter++ == 0) continue;
    coordinates[counter++] = std::stod(tok);
  }
  data->getVertices()->push_back(coordinates);
}

void Parser::addFacet(Data *data, const string &line) {
  std::vector<int> facets;
  stringstream iss(line);
  string tok;
  int iter = 0;
  while (getline(iss, tok, ' ')) {
    if (iter++ == 0) continue;
    facets.push_back(std::stod(tok));
  }
  data->getFacets()->push_back(facets);
}

s21::Data *s21::Parser::obtainData(const std::string &file_path) {
  Data *data = new Data();
  std::fstream file_name(file_path);
  if (!file_name.is_open()) throw std::runtime_error("File error!");
  std::string str;
  while (!file_name.eof()) {
    getline(file_name, str);
    if (str[0] == 'v') {
      addVertice(data, str);
    } else if (str[0] == 'f') {
      addFacet(data, str);
    }
  }
  fillLines(data);
  file_name.close();
  return data;
}

void Parser::fillLines(Data *data) {
  vector<vector<int>> *facets = data->getFacets();
  int facet_rows = facets->size();
  set<array<int, 2>> *lines = data->getLines();
  for (int i = 0; i < facet_rows; ++i) {
    vector<int> *facet = &(facets->at(i));
    int v_in_facet = facet->size();
    for (int j = 0; j < v_in_facet; ++j) {
      int start_index = facet->at(j);
      int end_index = (j == v_in_facet - 1) ? facet->at(0) : facet->at(j + 1);
      if (end_index < start_index) std::swap(start_index, end_index);
      array<int, 2> line = {start_index, end_index};
      if (start_index != end_index) lines->insert(line);
    }
  }
}
