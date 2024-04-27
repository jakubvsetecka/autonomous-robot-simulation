/**
 * @file robot.cpp
 * @brief This file provides the implementation of the Robot class.
 * @authors Jakub Všetečka, Tomáš Hobza
 */

#include "robot.h"

Robot::Robot(std::pair<float, float> position, float dimension, double angle, double velocity, double detectDistance)
    : GameObject(position, dimension, angle, velocity), detectDistance(detectDistance) {
    hitboxType = CIRCLE;
}

void Robot::update() {
    // TODO: Implement the update method
}