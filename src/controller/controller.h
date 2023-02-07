#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <array>
#include <string>
#include <vector>

#include "../model/data.h"
#include "../model/parser.h"
#include "../model/transformer.h"

using std::array;
using std::vector;

namespace s21 {
class Controller {
 public:
  Data* obtainData(const std::string& path);
  void scale(Data* data, double scale);
  void rotate(Data* data, double angle, Axis axis);
  void move(Data* data, double moving, Axis axis);

  Controller();
  ~Controller();
};
}  // namespace s21

#endif  // CONTROLLER_H
