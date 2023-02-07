#include "data_save.h"

#include <array>
#include <vector>

using namespace s21;

DataSave::DataSave(vector<array<double, 3>> vertices) : vertices_(vertices){};

DataSave::DataSave(){};

DataSave::~DataSave() { vertices_.clear(); };

const vector<array<double, 3>> DataSave::getVertices() const {
  return vertices_;
}
