#ifndef DATA_SAVE_H
#define DATA_SAVE_H

#include <array>
#include <vector>

using std::array;
using std::vector;

namespace s21 {
class DataSave {
 public:
  explicit DataSave(vector<array<double, 3>> vertices);
  DataSave();
  ~DataSave();

  const vector<array<double, 3>> getVertices() const;

 private:
  vector<array<double, 3>> vertices_;
};
}  // namespace s21

#endif  // DATA_SAVE_H
