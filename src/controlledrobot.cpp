/**
 * @file controlledrobot.cpp
 * @brief This file provides the implementation of the ControlledRobot class.
 * @authors Jakub Všetečka, Tomáš Hobza
 */

#include "controlledrobot.h"
#include <QDebug>

ControlledRobot::ControlledRobot(std::pair<float, float> position, float dimension, double angle, double velocity)
    : Robot(position, dimension, angle, velocity) {
}

void ControlledRobot::update() {
    // moveBy(angleDir.getX(), angleDir.getY());
}

void ControlledRobot::handleCollision() {
    qDebug() << "ControlledRobot collided with another object";
}