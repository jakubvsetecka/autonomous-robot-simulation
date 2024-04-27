/**
 * @file robot.h
 * @brief This file provides the definition of the Robot class.
 * @authors Jakub Všetečka, Tomáš Hobza
 */

#ifndef ROBOT_H
#define ROBOT_H

#include "gameobject.h"

class Robot : public GameObject {
  public:
    Robot(std::pair<float, float> position = std::pair<float, float>(0, 0), float dimension = 25.0, double angle = 0.0, double velocity = 0.0, double detectDistance = 50);

    void update() override;
    virtual void handleCollision() = 0;

  private:
    double detectDistance;
};

#endif // ROBOT_H