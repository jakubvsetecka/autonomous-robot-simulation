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
    AutonomousRobot(std::pair<float, float> position = std::pair<float, float>(0, 0), float dimension = 25.0, double angle = 0.0, double velocity = 0.0);

    void update() override;
    void handleCollision() override;

  protected:
    int rotationAmount = 1;
    int state = -1;
    bool rotateRight = true;
};

#endif // AUTONOMOUSROBOT_H