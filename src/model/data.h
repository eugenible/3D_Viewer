#ifndef DATA_H
#define DATA_H

#include <array>
#include <set>
#include <vector>

#include "data_save.h"

using std::array;
using std::set;
using std::vector;

namespace s21 {
class Data {
 public:
  Data();
  ~Data();
  vector<array<double, 3>>* getVertices();
  vector<vector<int>>* getFacets();
  set<array<int, 2>>* getLines();

  // Сохранение состояния вершин (Паттерн Memento)
  DataSave save();

  void loadSavedData(const DataSave& data);

 private:
  vector<array<double, 3>>* vertices_;
  vector<vector<int>>* facets_;
  set<array<int, 2>>* lines_;  // хранит индексы концов линий

  Data(const Data& other);
  Data& operator=(const Data& other);
};
}  // namespace s21

#endif  // DATA_H
