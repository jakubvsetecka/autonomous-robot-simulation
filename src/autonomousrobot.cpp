/**
 * @file autonomousrobot.cpp
 * @brief This file provides the implementation of the AutonomousRobot class.
 * @authors Jakub Všetečka, Tomáš Hobza
 */

#include "autonomousrobot.h"
#include <QDebug>

AutonomousRobot::AutonomousRobot(std::pair<float, float> position, float dimension, double angle, double velocity)
    : Robot(position, dimension, angle, velocity) {}

void AutonomousRobot::update() {
    switch (state) {
    case -1:
        position.first += angleDir.magnitude * angleDir.getX();
        position.second += angleDir.magnitude * angleDir.getY();
        break;
    default:
        if (rotateRight) {
            angleDir.rotate(1);
        } else {
            angleDir.rotate(-1);
        }
        if (state > rotationAmount) {
            state = -1;
        } else {
            state++;
        }
        break;
    }
}

void AutonomousRobot::handleCollision() {
    qDebug() << "AutonomousRobot collided with another object";
}