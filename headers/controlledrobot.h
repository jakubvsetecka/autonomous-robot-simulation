/**
 * @file controlledrobot.h
 * @brief This file provides the definition of the ControlledRobot class.
 * @authors Jakub Všetečka, Tomáš Hobza
 */

#ifndef CONTROLLEDROBOT_H
#define CONTROLLEDROBOT_H

#include "robot.h"

class ControlledRobot : public Robot {
  public:
    ControlledRobot(std::pair<float, float> position = std::pair<float, float>(0, 0), float dimension = 25.0, double angle = 0.0, double velocity = 0.0);

    void update() override;
    void handleCollision() override;
};

#endif // CONTROLLEDROBOT_H