/**
 * @file robot.cpp
 * @brief This file provides the implementation of the Robot class.
 * @authors Jakub Všetečka, Tomáš Hobza
 */

#include "robot.h"
#include <iostream>
#include <QDebug>

Robot::Robot(QGraphicsItem *parent, QPointF position, QPointF dimension, double angle, double velocity)
    : GameObject(parent, position, dimension, angle, velocity) {}

void Robot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QBrush brush(Qt::CrossPattern);
    painter->setBrush(brush);
    painter->drawEllipse(boundingRect());
    qreal x_center = dimension.x() / 2;
    qreal y_center = dimension.y() / 2;
    painter->drawLine(dimension.x(), y_center, x_center, y_center);
}

void Robot::update()
{
    moveBy(angleDir.getX(), angleDir.getY());
    setRotation(angleDir.angle);
}