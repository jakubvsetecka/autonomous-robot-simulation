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
    Robot(QGraphicsItem *parent = nullptr, QPointF position = QPointF(0, 0), QPointF dimension = QPointF(25, 25), double angle = 0.0, double velocity = 0.0);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void update() override;
};

#endif // ROBOT_H