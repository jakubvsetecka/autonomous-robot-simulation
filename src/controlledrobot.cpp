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

    switch (event->key()) {
    case Qt::Key_Left:
        // Change angle or perform movement to the left
        angleDir.angle -= 5 * M_PI / 180;
        break;
    case Qt::Key_Right:
        // Change angle or perform movement to the right
        angleDir.angle += 5 * M_PI / 180;
        break;
    case Qt::Key_Up:
        angleDir.magnitude = 10;
        moveBy(angleDir.getX(), angleDir.getY());
        break;
    case Qt::Key_Down:
        angleDir.magnitude = 0;
        break;
    default:
        QGraphicsItem::keyPressEvent(event); // Ensure other key events are processed
        return;
    }
    setRotation(angleDir.angle * 180 / M_PI); // Update the rotation

    setFocus();      // Ensure the item retains focus
    event->accept(); // Mark the event as handled
}

void ControlledRobot::update() {
    // moveBy(angleDir.getX(), angleDir.getY());
}

void ControlledRobot::handleCollision() {
    qDebug() << "ControlledRobot collided with another object";
}