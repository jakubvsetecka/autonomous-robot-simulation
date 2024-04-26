/**
 * @file controlledrobot.h
 * @brief This file provides the definition of the ControlledRobot class.
 * @authors Jakub Všetečka, Tomáš Hobza
 */

#ifndef CONTROLLEDROBOT_H
#define CONTROLLEDROBOT_H

#include "robot.h"
#include <QKeyEvent>

class ControlledRobot : public Robot {
  public:
    ControlledRobot(QGraphicsItem *parent = nullptr, QPointF position = QPointF(0, 0), QPointF dimension = QPointF(25, 25), double angle = 0.0, double velocity = 0.0)
        : Robot(parent, position, dimension, angle, velocity) {
        setFlag(QGraphicsItem::ItemIsFocusable);
    }

    void focusInEvent(QFocusEvent *event) override {
        qDebug() << "ControlledRobot gained focus";
    }

    void focusOutEvent(QFocusEvent *event) override {
        qDebug() << "ControlledRobot lost focus";
    }

    void keyPressEvent(QKeyEvent *event) override {

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
            angleDir.magnitude = 1;
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

    void update() override {
        // moveBy(angleDir.getX(), angleDir.getY());
    }
};

#endif // CONTROLLEDROBOT_H