#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "../../controller/controller.h"
#include "../../model/data.h"
#include "QtGifImage/src/gifimage/qgifimage.h"
#include "opengl.h"
#include "settings.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_openFileButton_clicked();

  void on_bgColorButton_clicked();

  void on_vColorButton_clicked();

  void on_lineColorButton_clicked();

  void on_LinesType_currentIndexChanged(int index);

  void on_VertexType_currentIndexChanged(int index);

  void on_ProjectionType_currentIndexChanged(int index);

  void on_lineWidth_valueChanged(int arg1);

  void on_vertexSize_valueChanged(int arg1);

  void on_XRotationScrollbar_valueChanged(int value);

  void on_YRotationScrollbar_valueChanged(int value);

  void on_ZRotationScrollbar_valueChanged(int value);

  void on_moveXPosBtn_clicked();

  void on_moveXNegBtn_clicked();

  void on_moveYPosBtn_clicked();

  void on_moveYNegBtn_clicked();

  void on_moveZPosBtn_clicked();

  void on_moveZNegBtn_clicked();

  void on_moveZPosBtn_2_clicked();

  void on_moveZNegBtn_2_clicked();

  void on_resetDrawing_clicked();

  void on_resetPosition_clicked();

  void on_jpegScreenshotBtn_clicked();

  void on_bmpScreenshotBtn_clicked();

  void makeScreenshot(const std::string &extension);

  void on_GifRecordButton_clicked();

  void on_StepForXrotation_textChanged();

  void on_StepForYrotation_textChanged();

  void on_StepForZrotation_textChanged();

 private:
  Data *obtainData(
      const QString &path);  // заполняет данные и передает их в opengl
                             //    void setNewInitialPosition(Data *data);

  void saveSettingsToFile();
  void loadSettingsFromFile();
  Controller *controller_;  // контроллер
  Data *data_;              // данные с точками
  DataSave savedData_;  // Сохраненное состояние вершин
  OpenGL *opengl_;      // opengl-виджет
  Settings *settings_;  // настройка параметров отображения
  Ui::MainWindow *ui;

  void showDataInfo(QString path);
  void clearOldData(Data *oldData);
};
#endif  // MAINWINDOW_H
