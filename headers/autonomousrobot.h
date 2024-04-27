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
    AutonomousRobot(QGraphicsItem *parent = nullptr, QPointF position = QPointF(0, 0), QPointF dimension = QPointF(25, 25), double angle = 0.0, double velocity = 0.0);

    void update() override;
    void handleCollision() override;

  protected:
    double rotaionAmount = 1;
    bool rotateRight = true;
};

#endif // AUTONOMOUSROBOT_H