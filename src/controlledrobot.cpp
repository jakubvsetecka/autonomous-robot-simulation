/**
 * @file controlledrobot.cpp
 * @brief This file provides the implementation of the ControlledRobot class.
 * @authors Jakub Všetečka, Tomáš Hobza
 */

#include "controlledrobot.h"
#include <QDebug>

ControlledRobot::ControlledRobot(QGraphicsItem *parent, QPointF position, QPointF dimension, double angle, double velocity)
    : Robot(parent, position, dimension, angle, velocity) {
    setFlag(QGraphicsItem::ItemIsFocusable);
}

void ControlledRobot::focusInEvent(QFocusEvent *event) {
    qDebug() << "ControlledRobot gained focus";
}

void ControlledRobot::focusOutEvent(QFocusEvent *event) {
    qDebug() << "ControlledRobot lost focus";
}

void ControlledRobot::keyPressEvent(QKeyEvent *event) {
    updateTransformOrigin(); // Update origin based on possibly updated bounding rectangle

    switch (event->key()) {
    case Qt::Key_Left:
        angleDir.rotate(5);
        break;
    case Qt::Key_Right:
        angleDir.rotate(-5);
        break;
    case Qt::Key_Up:
        angleDir.magnitude = 10;
        break;
    case Qt::Key_Down:
        angleDir.magnitude = 0;
        break;
    default:
        QGraphicsItem::keyPressEvent(event);
        return;
    }
    qDebug() << "Current Angle: " << angleDir.angle;
    qDebug() << "Position: " << pos();
    qDebug() << "Transformation Origin: " << transformOriginPoint();

    setRotation(angleDir.angle);
    moveBy(angleDir.getX(), angleDir.getY());
    setFocus();
    event->accept();
}

void ControlledRobot::update() {
    // moveBy(angleDir.getX(), angleDir.getY());
}

void ControlledRobot::handleCollision() {
    qDebug() << "ControlledRobot collided with another object";
}

void ControlledRobot::updateTransformOrigin() {
    QPointF center = boundingRect().center(); // Get the center of the bounding rectangle
    setTransformOriginPoint(center);          // Set the transformation origin to this center
}