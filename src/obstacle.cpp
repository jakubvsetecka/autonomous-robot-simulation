/**
 * @file obstacle.cpp
 * @brief This file provides the implementation of the Obstacle class.
 * @authors Jakub Všetečka, Tomáš Hobza
 */

#include "obstacle.h"

Obstacle::Obstacle(QGraphicsItem *parent, QPointF position, QPointF dimension, double angle)
    : GameObject(parent, position, dimension, angle, 0) {
    setRotation(angle);
}

void Obstacle::update() {
}