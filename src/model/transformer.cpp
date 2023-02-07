#include "transformer.h"

#include <cmath>

#include "data.h"

using namespace s21;
using std::array;
using std::vector;

void Transformer::scale(Data* data, double scale) {
  vector<array<double, 3>>* vertices = data->getVertices();
  size_t size = vertices->size();
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < 3; ++j) {
      vertices->at(i).at(j) *= scale;
    }
  }
}

void Transformer::rotate(Data* data, double angle, Axis axis) {
  angle *= M_PI / 180;
  vector<array<double, 3>>* vertices = data->getVertices();
  size_t size = vertices->size();

  for (int i = 0; i < size; ++i) {
    double temp_x = vertices->at(i).at(kX);
    double temp_y = vertices->at(i).at(kY);
    double temp_z = vertices->at(i).at(kZ);

    if (axis == kX) {
      vertices->at(i).at(kY) = cos(angle) * temp_y - sin(angle) * temp_z;
      vertices->at(i).at(kZ) = sin(angle) * temp_y + cos(angle) * temp_z;
    } else if (axis == kY) {
      vertices->at(i).at(kX) = cos(angle) * temp_x + sin(angle) * temp_z;
      vertices->at(i).at(kZ) = -sin(angle) * temp_x + cos(angle) * temp_z;
    } else if (axis == kZ) {
      vertices->at(i).at(kX) = cos(angle) * temp_x - sin(angle) * temp_y;
      vertices->at(i).at(kY) = sin(angle) * temp_x + cos(angle) * temp_y;
    }
  }
}

void Transformer::move(Data* data, double moving, Axis axis) {
  vector<array<double, 3>>* vertices = data->getVertices();
  size_t size = vertices->size();
  for (int i = 0; i < size; ++i) {
    vertices->at(i).at(axis) += moving;
  }
}
