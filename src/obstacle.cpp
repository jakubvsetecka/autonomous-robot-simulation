/**
 * @file obstacle.cpp
 * @brief This file contains the implementation of the Obstacle class.
 * @details It is a subclass of the QGraphicsRectItem class and represents an obstacle in the game.
 * @authors Tomáš Hobza, Jakub Všetečka
 * @date 02.05.2024
 */

#include "obstacle.hpp"

Obstacle::Obstacle(QGraphicsItem *parent)
    : QGraphicsRectItem(parent) {
    setRect(0, 0, 40, 40);
    setTransformOriginPoint(rect().center());
    QBrush brush(Qt::blue);
    setBrush(brush);
}

Obstacle::~Obstacle() {}

void Obstacle::setPos(qreal x, qreal y) {
    QGraphicsRectItem::setPos(x, y);
    emit paramsUpdated();
}

void Obstacle::setRotation(qreal angle) {
    QGraphicsRectItem::setRotation(angle);
    emit paramsUpdated();
}

void Obstacle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QGraphicsRectItem::paint(painter, option, widget);
}

QPointF Obstacle::getPos() {
    return QGraphicsRectItem::pos();
}

QJsonObject Obstacle::toJSON() {
    QJsonObject json;
    json["x"] = pos().x();
    json["y"] = pos().y();
    json["width"] = rect().width();
    json["rotation"] = rotation();
    return json;
}

Obstacle *Obstacle::fromJSON(const QJsonObject &json) {
    Obstacle *result = new Obstacle();
    QPointF pos;

    if (const QJsonValue v = json["width"]; v.isDouble())
        result->setRect(0, 0, v.toDouble(), v.toDouble());

    if (const QJsonValue v = json["x"]; v.isDouble())
        pos.setX(v.toDouble());

    if (const QJsonValue v = json["y"]; v.isDouble())
        pos.setY(v.toDouble());

    if (const QJsonValue v = json["rotation"]; v.isDouble())
        result->setRotation(v.toDouble());

    result->setPos(pos.x(), pos.y());

    return result;
}