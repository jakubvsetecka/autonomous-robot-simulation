#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "simulation.h"
#include <QGraphicsRectItem>
#include <QMainWindow>
#include <QTimer>

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
    void setupAnimation();

  private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    Simulation *simulation;

    void initScene();
    void updateAnimation(); // Method to update the animation
    void onAddObstacleClicked();
};
#endif // MAINWINDOW_H
