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
    moveBy(angleDir.getX(), angleDir.getY());
}

void AutonomousRobot::handleCollision() {
    qDebug() << "AutonomousRobot collided with another object";
}