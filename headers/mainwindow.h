#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsRectItem>
#include <QMainWindow>
#include <QTimer>
#include <QDebug>
#include <QKeyEvent>
#include "simulationengine.hpp"
#include "robutek.hpp"
#include "samorobutek.hpp"

QT_BEGIN_NAMESPACE
namespace Ui
{
  class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  void setupAnimation();

private:
  Ui::MainWindow *ui;
  SimulationEngine *simulationEngine;

  void initScene();
  void updateAnimation(); // Method to update the animation
  void onAddObstacleClicked();

protected:
  void showEvent(QShowEvent *event) override;
  void resizeEvent(QResizeEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;
  void keyReleaseEvent(QKeyEvent *event) override;
};
#endif // MAINWINDOW_H
