#ifndef SETTINGS_H
#define SETTINGS_H

#include <QColorDialog>
#include <QSettings>
#include <array>
#include <vector>

using std::array;
using std::vector;

namespace s21 {

enum LineType { kContinuous = 0, kDashed };
enum ProjectionType { kCentral = 0, kParallel };
enum VertexType { kCircle = 0, kSquare, kEmpty };

// Класс реализует паттерн singleton: для приложения существует один
// интегральный объект настроек, в котором хранятся все необходимые для
// отображения модели параметры
class Settings {
 public:
  // Получение Singleton-объекта
  static Settings& getInstance();

  QColor getBackgroundColor();
  QColor getVertexColor();
  QColor getLineColor();
  LineType getLineType();
  ProjectionType getProjectionType();
  VertexType getVertexType();
  double getVertexSize();
  double getLineWidth();

  bool getNeedOfProjectionChange();
  void setNeedOfProjectionChange(bool value);

  void resetPosition();

  void setBackgroundColor(const QColor& color);
  void setVertexColor(const QColor& color);
  void setLineColor(const QColor& color);

  void setLineType(const LineType& type);
  void setVertexType(const VertexType& type);
  void setProjectionType(const ProjectionType& type);

  void setVertexSize(int size);
  void setLineWidth(int width);

  double getScale();
  double getXAngle();
  double getYAngle();
  double getZAngle();
  double getXPos();
  double getYPos();
  double getZPos();

  void setScale(double value);
  void setXAngle(double value);
  void setYAngle(double value);
  void setZAngle(double value);
  void setXPos(double value);
  void setYPos(double value);
  void setZPos(double value);

  //  void clearOldInitialPosition();
  //  void setNewInitialPosition(const vector<array<double, 3>>& vertices);

 private:
  Settings();
  //  vector<array<double, 3>> initialPosition_;
  QColor background_color_ = QColorConstants::Gray;
  QColor line_color_ = QColorConstants::Black;
  QColor vertex_color_ = QColorConstants::Red;

  LineType line_type_ = kContinuous;
  ProjectionType projection_type_ = kCentral;
  VertexType vertex_type_ = kCircle;

  double vertex_size_;
  double line_width_;

  double scale_ = 1;
  double xAngle_ = 0;
  double yAngle_ = 0;
  double zAngle_ = 0;
  double xPos_ = 0;
  double yPos_ = 0;
  double zPos_ = 0;

  bool need_projection_change = false;
};
}  // namespace s21

#endif  // SETTINGS_H
