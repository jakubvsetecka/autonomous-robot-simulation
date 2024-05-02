/**
 * @file mainwindow.h
 * @brief This file contains the declaration of the MainWindow class.
 * @details It is a subclass of the QMainWindow class and represents the main window of the application.
 * @authors Tomáš Hobza, Jakub Všetečka
 * @date 02.05.2024
 */

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

/**
 * @class MainWindow
 * @brief A class to represent the main window of the application.
 * @details This class inherits from QMainWindow and provides the main window of the application.
 * @see QMainWindow
 */
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
    ExpandableButtonWidget *expandableWidget;
    OverlayWidget *overlay;

  private slots:
    /**
     * @brief Slot to handle the save button click event.
     *
     * @return void
     */
    void saveSimulation();

    /**
     * @brief Overridden event filter method to handle key press events.
     *
     * @param object The object that the event is being filtered for
     * @param event The event that is being filtered
     * @return bool Whether the event was handled
     */
    bool eventFilter(QObject *object, QEvent *event) override;

    /**
     * @brief Overriden show event method to handle the show event.
     *
     * @param event The show event
     * @return void
     */
    void showEvent(QShowEvent *event) override;

    /**
     * @brief Overriden resize event method to handle the resize event.
     *
     * @param event The resize event
     * @return void
     */
    void resizeEvent(QResizeEvent *event) override;

    /**
     * @brief Overriden close event method to handle the close event.
     *
     * @param event The close event
     * @return void
     */
    void mouseDoubleClickEvent(QMouseEvent *event) override;

    /**
     * @brief Overriden mouse press event method to handle the mouse press event.
     *
     * @param event The mouse press event
     * @return void
     */
    void mousePressEvent(QMouseEvent *event) override;

    /**
     * @brief Overriden mouse move event method to handle the mouse move event.
     *
     * @param event The mouse move event
     * @return void
     */
    void mouseMoveEvent(QMouseEvent *event) override;

    /**
     * @brief Overriden mouse release event method to handle the mouse release event.
     *
     * @param event The mouse release event
     * @return void
     */
    void mouseReleaseEvent(QMouseEvent *event) override;

    /**
     * @brief Slot to handle the horizontal slider value changed event.
     *
     * @param value The new value of the slider
     * @return void
     */
    void on_horizontalSlider_valueChanged(int value);

    /**
     * @brief Slot to handle toggling the list.
     *
     * @return void
     */
    void toggleList();

    /**
     * @brief Slot to handle the item double click event from the list.
     *
     * @param item The item that was double clicked
     * @return void
     */
    void handleItemDoubleClick(QListWidgetItem *item);

    /**
     * @brief Slot to handle clear button click event.
     *
     * @return void
     */
    void on_pushButton_clicked();

    /**
     * @brief Slot to handle rotate anticlockwise button click event.
     *
     * @return void
     */
    void goLeft();

    /**
     * @brief Slot to handle stop rotating button click event.
     *
     * @return void
     */
    void stopRotating();

    /**
     * @brief Slot to handle rotate clockwise button click event.
     *
     * @return void
     */
    void goRight();

    /**
     * @brief Slot to handle move forward button click event.
     *
     * @return void
     */
    void goStraight();

    /**
     * @brief Slot to handle stop moving button click event.
     *
     * @return void
     */
    void stopMoving();
};
#endif // MAINWINDOW_H
