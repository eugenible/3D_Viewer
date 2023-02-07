#ifndef TRANSFORMER_H
#define TRANSFORMER_H

#include "data.h"

namespace s21 {

enum Axis { kX = 0, kY, kZ };

class Transformer {
 public:
  static void scale(Data* data, double scale);
  static void rotate(Data* data, double angle, Axis axis);
  static void move(Data* data, double moving, Axis axis);
};
}  // namespace s21

#endif  // TRANSFORMER_H
