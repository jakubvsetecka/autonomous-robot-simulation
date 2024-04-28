/**
 * @file autonomousrobot.cpp
 * @brief This file provides the implementation of the AutonomousRobot class.
 * @authors Jakub Všetečka, Tomáš Hobza
 */

#include "autonomousrobot.h"
#include <QDebug>

AutonomousRobot::AutonomousRobot(QGraphicsItem *parent, QPointF position, QPointF dimension, double angle, double velocity)
    : Robot(parent, position, dimension, angle, velocity) {}

void AutonomousRobot::update()
{
    switch (state)
    {
    case -1:
    {
        if (angleDir.getMagnitude() > 0)
        {
            moveBy(angleDir.getX(), angleDir.getY());
        }
        break;
    }
    default:
        angleDir.rotate(1 ? rotateRight : -1);
        state = state >= rotationAmount ? -1 : state++;

        setRotation(angleDir.getAngle());
        break;
    }
}
