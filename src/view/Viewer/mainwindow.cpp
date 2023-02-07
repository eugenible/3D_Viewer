#include "mainwindow.h"

#include <QColorDialog>
#include <QPixmap>
#include <QTimer>
#include <iostream>
#include <sstream>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      controller_(new Controller()),
      data_(nullptr),
      savedData_(),
      opengl_(nullptr),
      settings_(&Settings::getInstance()),
      ui(new Ui::MainWindow) {
  ui->setupUi(this);
  loadSettingsFromFile();
  opengl_ = ui->openGLWidget;
  opengl_->setSettings(settings_);
  ui->LinesType->setCurrentIndex(settings_->getLineType());
  ui->VertexType->setCurrentIndex(settings_->getVertexType());
  ui->ProjectionType->setCurrentIndex(settings_->getProjectionType());
  ui->lineWidth->setValue(settings_->getLineWidth());
  ui->vertexSize->setValue(settings_->getVertexSize());
  ui->StepForXrotation->setValidator(new QIntValidator(0, 100, this));
  ui->StepForYrotation->setValidator(new QIntValidator(0, 100, this));
  ui->StepForZrotation->setValidator(new QIntValidator(0, 100, this));
}

void MainWindow::saveSettingsToFile() {
  QSettings settings("settings.ini", QSettings::IniFormat);
  settings.beginGroup("colors");
  settings.setValue("bg_color", settings_->getBackgroundColor());
  settings.setValue("vertex_color", settings_->getVertexColor());
  settings.setValue("line_color", settings_->getLineColor());
  settings.endGroup();

  settings.beginGroup("element_sizes");
  settings.setValue("vertex_size", settings_->getVertexSize());
  settings.setValue("line_width", settings_->getLineWidth());
  settings.endGroup();

  settings.beginGroup("view_types");
  settings.setValue("line_type", settings_->getLineType());
  settings.setValue("projection_type", settings_->getProjectionType());
  settings.setValue("vertex_type", settings_->getVertexType());
  settings.endGroup();
}

void MainWindow::loadSettingsFromFile() {
  QSettings settings("settings.ini", QSettings::IniFormat);
  settings.beginGroup("colors");
  QColor bg_color =
      settings.value("bg_color", QColorConstants::Gray).value<QColor>();
  QColor line_color =
      settings.value("line_color", QColorConstants::Black).value<QColor>();
  QColor vertex_color =
      settings.value("vertex_color", QColorConstants::Red).value<QColor>();
  settings.endGroup();

  settings.beginGroup("element_sizes");
  double vertex_size = settings.value("vertex_size", 3).toDouble();
  double line_width = settings.value("line_width", 3).toDouble();
  settings.endGroup();

  settings.beginGroup("view_types");
  LineType line_type =
      static_cast<LineType>(settings.value("line_type", 0).toInt());
  VertexType vertex_type =
      static_cast<VertexType>(settings.value("vertex_type", 0).toInt());
  ProjectionType projection_type =
      static_cast<ProjectionType>(settings.value("projection_type", 0).toInt());
  settings.endGroup();

  settings_->setBackgroundColor(bg_color);
  settings_->setLineColor(line_color);
  settings_->setVertexColor(vertex_color);
  settings_->setVertexSize(vertex_size);
  settings_->setLineWidth(line_width);
  settings_->setLineType(line_type);
  settings_->setVertexType(vertex_type);
  settings_->setProjectionType(projection_type);
}

MainWindow::~MainWindow() {
  saveSettingsToFile();
  delete data_;  // ДОБАВИТЬ УДАЛЕНИЕ ДАТЫ В ФУНКЦИИ СМЕНЫ ФАЙЛА !!!
  delete controller_;
  delete opengl_;  // надо ли?
  delete ui;
}

Data *MainWindow::obtainData(const QString &path) {
  std::string file_path = path.toStdString();
  return controller_->obtainData(file_path);
}

// void MainWindow::setNewInitialPosition(Data *data) {
//     settings_->clearOldInitialPosition();
//     settings_->setNewInitialPosition(*data->getVertices());
// }

void MainWindow::showDataInfo(QString path) {
  if (path.contains("/")) {
    path.remove(0, path.lastIndexOf("/") + 1);
  }
  ui->FileNameLabel->setText(path);
  ui->VertexesCount->setText(
      QString::number(data_->getVertices()->size(), 'g', 7));
  ui->EdgesCount->setText(QString::number(data_->getLines()->size(), 'g', 7));
}

void MainWindow::on_openFileButton_clicked() {
  QString file_path =
      QFileDialog::getOpenFileName(0, "Открыть", "../objects/", "*.obj");
  if (file_path.isEmpty()) return;
  Data *newData = obtainData(file_path);
  Data *oldData = data_;
  clearOldData(oldData);
  data_ = newData;
  savedData_ = data_->save();
  opengl_->setData(data_);
  showDataInfo(file_path);
  ui->openGLWidget->update();
}

void MainWindow::clearOldData(Data *oldData) {
  if (oldData != nullptr) {
    delete oldData;
  }
}

void MainWindow::on_bgColorButton_clicked() {
  QColorDialog cd;
  QColor color = cd.getColor(settings_->getBackgroundColor());
  if (color.isValid()) settings_->setBackgroundColor(color);
}

void MainWindow::on_vColorButton_clicked() {
  QColorDialog cd;
  QColor color = cd.getColor(settings_->getVertexColor());
  if (color.isValid()) settings_->setVertexColor(color);
}

void MainWindow::on_lineColorButton_clicked() {
  QColorDialog cd;
  QColor color = cd.getColor(settings_->getLineColor());
  if (color.isValid()) settings_->setLineColor(color);
}

void MainWindow::on_LinesType_currentIndexChanged(int index) {
  LineType type = static_cast<LineType>(index);
  settings_->setLineType(type);
}

void MainWindow::on_VertexType_currentIndexChanged(int index) {
  VertexType type = static_cast<VertexType>(index);
  settings_->setVertexType(type);
}

void MainWindow::on_ProjectionType_currentIndexChanged(int index) {
  ProjectionType type = static_cast<ProjectionType>(index);
  settings_->setProjectionType(type);
  settings_->setNeedOfProjectionChange(true);
}

void MainWindow::on_lineWidth_valueChanged(int arg1) {
  settings_->setLineWidth(arg1);
}

void MainWindow::on_vertexSize_valueChanged(int arg1) {
  settings_->setVertexSize(arg1);
}

void MainWindow::on_StepForXrotation_textChanged() {
  ui->XRotationScrollbar->setSingleStep(ui->StepForXrotation->text().toInt());
}

void MainWindow::on_XRotationScrollbar_valueChanged(int value) {
  double rotateAngle = value - settings_->getXAngle();
  settings_->setXAngle(value);
  controller_->rotate(data_, rotateAngle, kX);
}

void MainWindow::on_StepForYrotation_textChanged() {
  ui->YRotationScrollbar->setSingleStep(ui->StepForYrotation->text().toInt());
}

void MainWindow::on_YRotationScrollbar_valueChanged(int value) {
  double rotateAngle = value - settings_->getYAngle();
  settings_->setYAngle(value);
  controller_->rotate(data_, rotateAngle, kY);
}

void MainWindow::on_StepForZrotation_textChanged() {
  ui->ZRotationScrollbar->setSingleStep(ui->StepForZrotation->text().toInt());
}

void MainWindow::on_ZRotationScrollbar_valueChanged(int value) {
  double rotateAngle = value - settings_->getZAngle();
  settings_->setZAngle(value);
  controller_->rotate(data_, rotateAngle, kZ);
}

void MainWindow::on_moveXPosBtn_clicked() {
  double step = ui->xStepSize->value();
  controller_->move(data_, step, kX);
}

void MainWindow::on_moveXNegBtn_clicked() {
  double step = ui->xStepSize->value();
  controller_->move(data_, -step, kX);
}

void MainWindow::on_moveYPosBtn_clicked() {
  double step = ui->yStepSize->value();
  controller_->move(data_, step, kY);
}

void MainWindow::on_moveYNegBtn_clicked() {
  double step = ui->yStepSize->value();
  controller_->move(data_, -step, kY);
}

void MainWindow::on_moveZPosBtn_clicked() {
  double step = ui->zStepSize->value();
  controller_->move(data_, step, kZ);
}

void MainWindow::on_moveZNegBtn_clicked() {
  double step = ui->zStepSize->value();
  controller_->move(data_, -step, kZ);
}

void MainWindow::on_moveZPosBtn_2_clicked() {
  double scale = 1 + ui->scaleSize->value() / 100.0;
  controller_->scale(data_, scale);
}

void MainWindow::on_moveZNegBtn_2_clicked() {
  double scale = 1 - ui->scaleSize->value() / 100.0;
  controller_->scale(data_, scale);
}

void MainWindow::on_resetDrawing_clicked() {
  QSettings settings("settings.ini", QSettings::IniFormat);
  settings.clear();
  loadSettingsFromFile();
  ui->LinesType->setCurrentIndex(settings_->getLineType());
  ui->VertexType->setCurrentIndex(settings_->getVertexType());
  ui->ProjectionType->setCurrentIndex(settings_->getProjectionType());
  ui->lineWidth->setValue(settings_->getLineWidth());
  ui->vertexSize->setValue(settings_->getVertexSize());
}

void MainWindow::on_resetPosition_clicked() {
  ui->XRotationScrollbar->setValue(0);
  ui->YRotationScrollbar->setValue(0);
  ui->ZRotationScrollbar->setValue(0);
  settings_->resetPosition();
  if (data_ != nullptr) data_->loadSavedData(savedData_);
}

void MainWindow::makeScreenshot(const std::string &extension) {
  QPixmap screenshot(opengl_->size());
  opengl_->render(&screenshot);
  std::string ext = (extension == ".jpeg") ? "JPEG" : "BMP";
  QString FileName = QFileDialog::getSaveFileName(
      this, "Choose a location for screenshot", QDir::homePath(),
      (extension == ".jpeg") ? "JPEG (*.jpeg)" : "BMP (*.bmp)");
  screenshot.save(FileName);
}

void MainWindow::on_jpegScreenshotBtn_clicked() { makeScreenshot(".jpeg"); }

void MainWindow::on_bmpScreenshotBtn_clicked() { makeScreenshot(".bmp"); }

void MainWindow::on_GifRecordButton_clicked() {
  QGifImage *gif = new QGifImage(QSize(640, 480));
  gif->setDefaultDelay(100);
  glRotated(10, 0, 1, 0);
  QTimer *time = new QTimer(this);
  time->start(100);
  while (1) {
    if (gif->frameCount() < 50) {
      QImage image;
      controller_->rotate(data_, 7.2, kY);
      update();
      image = ui->openGLWidget->grabFramebuffer();
      image = image.scaled(640, 480, Qt::IgnoreAspectRatio,
                           Qt::SmoothTransformation);
      gif->addFrame(image);
    } else {
      QString FileName = QFileDialog::getSaveFileName(
          this, "Open a file", QDir::homePath(), "GIF (*.gif)");
      gif->save(FileName);
      time->stop();
      delete gif;
      break;
    }
  }
}
