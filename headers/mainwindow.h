#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "autorobot.hpp"
#include "expbuttonwidget.hpp"
#include "obstacle.hpp"
#include "robot.hpp"
#include "simulationengine.hpp"
#include <QDebug>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QMainWindow>
#include <QMouseEvent>
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
    SimulationEngine *simulationEngine;

    void initScene();
    void updateAnimation(); // Method to update the animation

  protected:
    void showEvent(QShowEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event);
    void onAddObstacleClicked();
    void onAddAutoRobotClicked();
    void onAddControlledRobotClicked();

    ExpandableButtonWidget *expandableWidget;
};
#endif // MAINWINDOW_H
