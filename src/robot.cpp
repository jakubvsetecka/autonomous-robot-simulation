/**
 * @file robot.cpp
 * @brief This file provides the implementation of the Robot class.
 * @authors Jakub Všetečka, Tomáš Hobza
 */

#include "robot.h"
#include <iostream>
#include <QDebug>

Robot::Robot(QGraphicsItem *parent, QPointF position, QPointF dimension, double angle, double velocity)
    : GameObject(parent, position, dimension, angle, velocity)
{
    setPos(position);
}

void Robot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QBrush brush(color);
    painter->setBrush(brush);
    painter->drawEllipse(0, 0, dimension.x(), dimension.y());
    qreal x_center = dimension.x() / 2;
    qreal y_center = dimension.y() / 2;
    painter->drawLine(x_center, y_center, x_center + collisionLookahead, y_center);

    painter->setPen(QPen(Qt::red, 1));
    painter->drawEllipse(collisionLookahead, 0, dimension.x(), dimension.y());
}

QRectF Robot::boundingRect() const
{
    qreal extra = (dimension.x() / 2) * 10; // extra width to include the line
    return QRectF(0, 0, dimension.x() + extra, dimension.y());
}

QPointF Robot::pos() const
{
    return QGraphicsItem::pos() + QPointF(dimension.x() / 2, dimension.y() / 2);
}

bool Robot::checkCollisions()
{
    bool isColliding = false;
    // Check if the robot is not going out of the scene
    if (scene() != nullptr)
    {
        // Get the scene rectangle
        QRectF sceneRect = scene()->sceneRect();

        // Get the inner rectangle of the scene (use the dimension of the robot as a margin as the robot is a circle and the dimension is the diameter of the circle)
        QRectF sceneInnerRect = sceneRect.adjusted(dimension.x() / 2, dimension.y() / 2, -dimension.x() / 2, -dimension.y() / 2);

        QPointF nextPos = pos() + angleDir.getPointForMagnitude(collisionLookahead);

        scene()->addRect(sceneInnerRect, QPen(Qt::red));

        if (!sceneInnerRect.contains(nextPos)) // || !sceneInnerRect.contains(pos() + angleDir.getPoint()))
        {
            qDebug() << "Robot is going out of the scene!";
            isColliding = true;
        }
    }

    return isColliding;
}

void Robot::update()
{
    if (angleDir.getMagnitude() > 0)
    {
        if (!checkCollisions())
        {
            moveBy(angleDir.getX(), angleDir.getY());
        }
    }

    if (rotation() != angleDir.getAngle())
    {
        setRotation(angleDir.getAngle());
    }
}