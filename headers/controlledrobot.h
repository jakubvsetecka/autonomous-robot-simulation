/**
 * @file controlledrobot.h
 * @brief This file provides the definition of the ControlledRobot class.
 * @authors Jakub Všetečka, Tomáš Hobza
 */

#ifndef CONTROLLEDROBOT_H
#define CONTROLLEDROBOT_H

#include "robot.h"
#include <QKeyEvent>

class ControlledRobot : public Robot {
  public:
    ControlledRobot(QGraphicsItem *parent = nullptr, QPointF position = QPointF(0, 0), QPointF dimension = QPointF(25, 25), double angle = 0.0, double velocity = 0.0);

    void focusInEvent(QFocusEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void update() override;
};

#endif // CONTROLLEDROBOT_H