#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "autorobot.hpp"
#include "checkablebutton.hpp"
#include "expbuttonwidget.hpp"
#include "gameobject.hpp"
#include "obstacle.hpp"
#include "overlaywidget.hpp"
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
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event);
    void onAddObstacleClicked();
    void onAddAutoRobotClicked();
    void onAddControlledRobotClicked();
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event) override;

    ExpandableButtonWidget *expandableWidget;
    OverlayWidget *overlay;
};
#endif // MAINWINDOW_H
