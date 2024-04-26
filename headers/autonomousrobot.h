/**
 * @file autonomousrobot.h
 * @brief This file provides the definition of the AutonomousRobot class.
 * @authors Jakub Všetečka, Tomáš Hobza
*/

#ifndef AUTONOMOUSROBOT_H
#define AUTONOMOUSROBOT_H

#include "robot.h"

class AutonomousRobot : public Robot {
  public:
    AutonomousRobot(QGraphicsItem *parent = nullptr, QPointF position = QPointF(0, 0), QPointF dimension = QPointF(25, 25), double angle = 0.0, double velocity = 0.0)
        : Robot(parent, position, dimension, angle, velocity) {}

    void update() override {
        // Example behavior: move randomly within bounds
        moveBy(angleDir.getX(), angleDir.getY());
    }

  protected:
    double detectDistance = 50;
    double rotaionAmount = 1;
    bool rotateRight = true;
};

#endif // AUTONOMOUSROBOT_H