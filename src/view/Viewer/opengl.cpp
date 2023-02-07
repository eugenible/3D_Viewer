#include "opengl.h"

#include <math.h>

#include "../../model/transformer.h"

// delete later
#include <chrono>
#include <thread>
// delete later

#include <iostream>
#include <set>

using namespace s21;

OpenGL::OpenGL(QWidget* parent)
    : QOpenGLWidget{parent}, data_(nullptr), settings_(nullptr) {}

void OpenGL::perspectiveGL(GLdouble fovY, GLdouble aspect, GLdouble zNear,
                           GLdouble zFar) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  const GLdouble pi = 3.1415926535897932384626433832795;
  GLdouble fW, fH;
  fH = tan(fovY / 360 * pi) * zNear;
  fW = fH * aspect;
  if (settings_->getProjectionType() == kCentral) {
    glFrustum(-fW, fW, -fH, fH, zNear, zFar);
  } else if (settings_->getProjectionType() == kParallel) {
    glOrtho(-fW, fW, -fH, fH, zNear, zFar);
  }
  update();
}

void OpenGL::drawVertices() {
  if (settings_->getVertexType() == kEmpty) return;
  vector<array<double, 3>>* vertices = data_->getVertices();
  size_t verticeCount = vertices->size();
  QColor color = settings_->getVertexColor();
  glColor3d(color.redF(), color.greenF(), color.blueF());
  glPointSize(settings_->getVertexSize());
  if (settings_->getVertexType() == kCircle) {
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  } else if (settings_->getVertexType() == kSquare) {
    glDisable(GL_POINT_SMOOTH);
  }
  for (size_t i = 0; i < verticeCount; ++i) {
    array<double, 3>* vertex = &(vertices->at(i));
    glBegin(GL_POINTS);
    glVertex3d(vertex->at(0), vertex->at(1), vertex->at(2));
    glEnd();
  }
}

void OpenGL::drawLines() {
  set<array<int, 2>>* lines = data_->getLines();
  vector<array<double, 3>>* vertices = data_->getVertices();
  QColor color = settings_->getLineColor();
  glColor3d(color.redF(), color.greenF(), color.blueF());
  glLineWidth(settings_->getLineWidth());
  glEnable(GL_LINE_STIPPLE);
  if (settings_->getLineType() == kDashed)
    glLineStipple(1, 0x00FF);
  else if (settings_->getLineType() == kContinuous)
    glLineStipple(1, 0xFFFF);
  for (auto& line : *lines) {
    int start = line.at(0);
    int end = line.at(1);
    glBegin(GL_LINES);
    glVertex3d(vertices->at(start - 1).at(0), vertices->at(start - 1).at(1),
               vertices->at(start - 1).at(2));
    glVertex3d(vertices->at(end - 1).at(0), vertices->at(end - 1).at(1),
               vertices->at(end - 1).at(2));
    glEnd();
  }
}

void OpenGL::draw() {
  drawLines();
  drawVertices();
}

void OpenGL::initializeGL() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
}

void OpenGL::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  perspectiveGL(70, 1, 1, 100);
}

void OpenGL::paintGL() {
  update();
  if (settings_->getNeedOfProjectionChange()) {
    perspectiveGL(70, 1, 1, 100);  // TYT
    settings_->setNeedOfProjectionChange(false);
  }

  QColor background_color = settings_->getBackgroundColor();
  glClearColor(background_color.redF(), background_color.greenF(),
               background_color.blueF(), 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0, 0, -35);
  if (data_ != nullptr) draw();
}

void OpenGL::setData(Data* data) { data_ = data; }

void OpenGL::setSettings(Settings* settings) { settings_ = settings; }
