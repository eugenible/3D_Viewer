#include "settings.h"

using namespace s21;

Settings::Settings() : vertex_size_(0), line_width_(0){};

Settings& Settings::getInstance() {
  static Settings settings;
  return settings;
}

QColor Settings::getBackgroundColor() { return background_color_; };

QColor Settings::getVertexColor() { return vertex_color_; };

QColor Settings::getLineColor() { return line_color_; };

void Settings::setBackgroundColor(const QColor& color) {
  background_color_ = color;
};

void Settings::setVertexColor(const QColor& color) { vertex_color_ = color; };

void Settings::setLineColor(const QColor& color) { line_color_ = color; };

LineType Settings::getLineType() { return line_type_; }

ProjectionType Settings::getProjectionType() { return projection_type_; }

VertexType Settings::getVertexType() { return vertex_type_; }

double Settings::getVertexSize() { return vertex_size_; }

double Settings::getLineWidth() { return line_width_; }

bool Settings::getNeedOfProjectionChange() { return need_projection_change; }

void Settings::setNeedOfProjectionChange(bool value) {
  need_projection_change = value;
}

void Settings::setLineType(const LineType& type) { line_type_ = type; }

void Settings::setVertexType(const VertexType& type) { vertex_type_ = type; }

void Settings::setProjectionType(const ProjectionType& type) {
  projection_type_ = type;
}

void Settings::setVertexSize(int size) { vertex_size_ = size; }

void Settings::setLineWidth(int width) { line_width_ = width; }

double Settings::getScale() { return scale_; }

double Settings::getXAngle() { return xAngle_; }

double Settings::getYAngle() { return yAngle_; }

double Settings::getZAngle() { return zAngle_; }

double Settings::getXPos() { return xPos_; }

double Settings::getYPos() { return yPos_; }

double Settings::getZPos() { return zPos_; }

void Settings::setScale(double value) { scale_ = value; }

void Settings::setXAngle(double value) { xAngle_ = value; }

void Settings::setYAngle(double value) { yAngle_ = value; }

void Settings::setZAngle(double value) { zAngle_ = value; }

void Settings::setXPos(double value) { xPos_ = value; }

void Settings::setYPos(double value) { yPos_ = value; }

void Settings::setZPos(double value) { zPos_ = value; }

void Settings::resetPosition() {
  scale_ = 1;
  xAngle_ = 0;
  yAngle_ = 0;
  zAngle_ = 0;
  xPos_ = 0;
  yPos_ = 0;
  zPos_ = 0;
}

// void Settings::clearOldInitialPosition() {
//     initialPosition_.clear();
// }

// void Settings::setNewInitialPosition(const vector<array<double, 3>>&
// vertices) {
//     initialPosition_ = vertices;
// }
