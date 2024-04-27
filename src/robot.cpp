/**
 * @file robot.cpp
 * @brief This file provides the implementation of the Robot class.
 * @authors Jakub Všetečka, Tomáš Hobza
 */

#include "robot.h"

Robot::Robot(QGraphicsItem *parent, QPointF position, QPointF dimension, double angle, double velocity)
    : GameObject(parent, position, dimension, angle, velocity) {}

void Robot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QBrush brush(Qt::CrossPattern);
    painter->setBrush(brush);
    painter->drawEllipse(boundingRect());
}

void Robot::update()
{
    moveBy(angleDir.getX(), angleDir.getY());
    setRotation(angleDir.angle);
}