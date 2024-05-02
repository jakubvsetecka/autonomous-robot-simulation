/**
 * @file expbutton.cpp
 * @brief This file contains the implementation of the ExpButton class.
 * @details It is a subclass of the QPushButton class and represents an expandable button.
 * @authors Tomáš Hobza, Jakub Všetečka
 * @date 02.05.2024
 */

#include "expbutton.hpp"

ExpButton::ExpButton(const QString &text, QWidget *parent)
    : QPushButton(text, parent) {
    setMouseTracking(true); // Enable mouse tracking
}

void ExpButton::mousePressEvent(QMouseEvent *event) {
    QPushButton::mousePressEvent(event);
    emit pressed();
}