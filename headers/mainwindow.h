#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "autorobot.hpp"
#include "checkablebutton.hpp"
#include "expbuttonwidget.hpp"
#include "gameobject.hpp"
#include "obstacle.hpp"
#include "overlaywidget.hpp"
#include "popupsavewindow.h"
#include "robot.hpp"
#include "simulationengine.hpp"
#include <QDebug>
#include <QGraphicsRectItem>

#include <QKeyEvent>
#include <QListWidget>
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
    QListWidget *listWidget;

    void initScene();
    void updateAnimation(); // Method to update the animation

  protected:
    void showEvent(QShowEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void loadSimulation();
    void saveSimulation();
    bool eventFilter(QObject *object, QEvent *event);

    ExpandableButtonWidget *expandableWidget;
    OverlayWidget *overlay;

  private slots:
    void on_horizontalSlider_valueChanged(int value);
    void toggleList();
    void handleItemDoubleClick(QListWidgetItem *item);
    void on_pushButton_clicked();
};
#endif // MAINWINDOW_H
