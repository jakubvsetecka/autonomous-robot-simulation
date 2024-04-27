/**
 * @file gameobject.cpp
 * @brief This file provides the implementation of the GameObject class.
 * @authors Jakub Všetečka, Tomáš Hobza
 */

#include "gameobject.h"
#include <QBrush>
#include <QJsonValue>

GameObject::GameObject(QGraphicsItem *parent, QPointF position, QPointF dimension, double angle, double velocity)
    : QGraphicsItem(parent), angleDir(angle, velocity), dimension(dimension) {
    setTransformOriginPoint(boundingRect().center());
    setPos(position);
}

GameObject::~GameObject() {}

QRectF GameObject::boundingRect() const {
    return QRectF(0, 0, dimension.x(), dimension.y());
}

void GameObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QBrush brush(Qt::CrossPattern);
    painter->setBrush(brush);
    painter->drawRect(boundingRect());
}

void GameObject::update() {
    moveBy(angleDir.getX(), angleDir.getY());
    setRotation(angleDir.angle);
}

QJsonValue GameObject::toJson() const {
    // Convert object to JSON
    // Placeholder for JSON conversion code
}

GameObject *GameObject::fromJson(const QJsonObject &obj) {
    // Create object from JSON
    // Placeholder for JSON object creation code
}

void GameObject::enslaveToTime(float frameTTL) {
    qreal dx = x() * frameTTL;
    qreal dy = y() * frameTTL;
    setPos(dx, dy);
}
