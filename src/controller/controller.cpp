#include "controller.h"

using namespace s21;

Data *Controller::obtainData(const std::string &path) {
  return Parser::obtainData(path);
}

void Controller::scale(Data *data, double scale) {
  if (data != nullptr) Transformer::scale(data, scale);
}

void Controller::rotate(Data *data, double angle, Axis axis) {
  if (data != nullptr) Transformer::rotate(data, angle, axis);
}

void Controller::move(Data *data, double moving, Axis axis) {
  if (data != nullptr) Transformer::move(data, moving, axis);
}

Controller::Controller(){};

Controller::~Controller() {}
