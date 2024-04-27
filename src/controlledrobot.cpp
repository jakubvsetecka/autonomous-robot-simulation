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
        if (angleDir.magnitude <= 0) {
            angleDir.rotate(-5);
        }
        break;
    case Qt::Key_Right:
        // Change angle or perform movement to the right
        if (angleDir.magnitude <= 0) {
            angleDir.rotate(5);
        }
        break;
    case Qt::Key_Up:
        angleDir.magnitude = 100;
        break;
    case Qt::Key_Down:
        angleDir.magnitude = 0;
        break;
    default:
        QGraphicsItem::keyPressEvent(event); // Ensure other key events are processed
        return;
    }

    setFocus();      // Ensure the item retains focus
    event->accept(); // Mark the event as handled
}

void ControlledRobot::keyReleaseEvent(QKeyEvent *event) {

    angleDir.setMagnitude(0);

    setFocus();      // Ensure the item retains focus
    event->accept(); // Mark the event as handled
}

void ControlledRobot::update() {
    moveByWrapper(angleDir.getX(), angleDir.getY());
    setRotation(angleDir.getAngle()); // Update the rotation
}

void ControlledRobot::handleCollision() {
    qDebug() << "ControlledRobot collided with another object";
}

void ControlledRobot::updateTransformOrigin() {
    QPointF center = boundingRect().center(); // Get the center of the bounding rectangle
    setTransformOriginPoint(center);          // Set the transformation origin to this center
}