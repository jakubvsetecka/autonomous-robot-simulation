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
    Obstacle(QGraphicsItem *parent = nullptr, QPointF position = QPointF(0, 0), QPointF dimension = QPointF(25, 25), double angle = 0.0)
        : GameObject(parent, position, dimension, angle, 0) {
        setRotation(angle);
    }

    void update() override {
        // Obstacles do not move
    }
};

#endif // OBSTACLE_H