#ifndef OPENGL_H
#define OPENGL_H

#include <QFileDialog>
#include <QOpenGLWidget>
#include <QScrollBar>
#include <QWidget>

#include "../../controller/controller.h"
#include "../../model/data.h"
#include "qscrollbar.h"
#include "settings.h"

using namespace s21;

class OpenGL : public QOpenGLWidget {
  Q_OBJECT
 private:
  Data *data_;
  Settings *settings_;

  void draw();
  void drawLines();
  void drawVertices();
  void perspectiveGL(GLdouble fovY, GLdouble aspect, GLdouble zNear,
                     GLdouble zFar);

 protected:
  void initializeGL();
  void resizeGL(int w, int h);
  void paintGL();

 public:
  void setData(Data *data);
  void setSettings(Settings *settings);
  explicit OpenGL(QWidget *parent = nullptr);

 signals:
};

#endif  // OPENGL_H
