/**
 * @file gameobject.cpp
 * @brief This file provides the implementation of the GameObject class.
 * @authors Jakub Všetečka, Tomáš Hobza
 */

#include "gameobject.h"
#include <QBrush>
#include <QJsonValue>

GameObject::GameObject(QGraphicsItem *parent, QPointF position, QPointF dimension, double angle, double velocity)
    : QGraphicsItem(parent), position(position), angleDir(angle, velocity), dimension(dimension) {
    setTransformOriginPoint(boundingRect().center());
}

GameObject::~GameObject() {}

QRectF GameObject::boundingRect() const {
    return QRectF(position.x(), position.y(), dimension.x(), dimension.y());
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
