#include "expbutton.hpp"

ExpButton::ExpButton(const QString &text, QWidget *parent)
    : QPushButton(text, parent) {
    setMouseTracking(true); // Enable mouse tracking
}

void ExpButton::mousePressEvent(QMouseEvent *event) {
    QPushButton::mousePressEvent(event);
    emit pressed();
}