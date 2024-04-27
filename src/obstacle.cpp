/**
 * @file obstacle.cpp
 * @brief This file provides the implementation of the Obstacle class.
 * @authors Jakub Všetečka, Tomáš Hobza
 */

#include "obstacle.h"

Obstacle::Obstacle(std::pair<float, float> position, float dimension, double angle)
    : GameObject(position, dimension, angle, 0) {}

void Obstacle::update() {
}