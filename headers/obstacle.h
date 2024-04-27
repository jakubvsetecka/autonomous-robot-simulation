/**
 * @file obstacle.h
 * @brief This file provides the definition of the Obstacle class.
 * @authors Jakub Všetečka, Tomáš Hobza
 */

#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "gameobject.h"

class Obstacle : public GameObject {
  public:
    Obstacle(std::pair<float, float> position = std::pair<float, float>(0, 0), float dimension = 25.0, double angle = 0.0);

    void update() override;
};

#endif // OBSTACLE_H