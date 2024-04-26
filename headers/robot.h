/**
 * @file robot.h
 * @brief This file provides the definition of the Robot class.
 * @authors Jakub Všetečka, Tomáš Hobza
 */

#ifndef ROBOT_H
#define ROBOT_H

#include "gameobject.h"

class Robot : public GameObject {
  public:
    Robot(QGraphicsItem *parent = nullptr, QPointF position = QPointF(0, 0), QPointF dimension = QPointF(25, 25), double angle = 0.0, double velocity = 0.0)
        : GameObject(parent, position, dimension, angle, velocity) {}

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override {
        QBrush brush(Qt::CrossPattern);
        painter->setBrush(brush);
        painter->drawEllipse(boundingRect());
    }

    void update() override {
        moveBy(angleDir.getX(), angleDir.getY());
        setRotation(angleDir.angle);
    }
};

#endif // ROBOT_H