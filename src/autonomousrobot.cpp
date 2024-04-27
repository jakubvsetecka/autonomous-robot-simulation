/**
 * @file autonomousrobot.cpp
 * @brief This file provides the implementation of the AutonomousRobot class.
 * @authors Jakub Všetečka, Tomáš Hobza
 */

#include "autonomousrobot.h"
#include <QDebug>

AutonomousRobot::AutonomousRobot(QGraphicsItem *parent, QPointF position, QPointF dimension, double angle, double velocity)
    : Robot(parent, position, dimension, angle, velocity) {}

void AutonomousRobot::update() {
    switch (state) {
    case -1: {
        moveBy(angleDir.getX(), angleDir.getY());
        break;
    }
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
        setRotation(angleDir.angle);
        break;
    }
}

void AutonomousRobot::handleCollision() {
    qDebug() << "AutonomousRobot collided with another object";
    state = 0;
}