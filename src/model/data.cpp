#include "data.h"

#include <array>
#include <set>
#include <vector>

using namespace s21;

Data::Data()
    : vertices_(new vector<array<double, 3>>()),
      facets_(new vector<vector<int>>()),
      lines_(new set<array<int, 2>>()) {}

Data::~Data() {
  delete vertices_;
  delete facets_;
  delete lines_;
}

vector<array<double, 3>>* Data::getVertices() { return vertices_; }

vector<vector<int>>* Data::getFacets() { return facets_; }

set<array<int, 2>>* Data::getLines() { return lines_; }

DataSave Data::save() { return DataSave(*vertices_); }

void Data::loadSavedData(const DataSave& data) {
  *vertices_ = data.getVertices();
}

Data::Data(const Data& other) {
  vertices_ = new vector<array<double, 3>>(*other.vertices_);
  facets_ = new vector<vector<int>>(*other.facets_);
  lines_ = new set<array<int, 2>>(*other.lines_);
}

Data& Data::operator=(const Data& other) {
  if (this != &other) {
    vertices_ = new vector<array<double, 3>>(*other.vertices_);
    facets_ = new vector<vector<int>>(*other.facets_);
    lines_ = new set<array<int, 2>>(*other.lines_);
  }
  return *this;
}
