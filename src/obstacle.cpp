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
}

void Obstacle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QGraphicsRectItem::paint(painter, option, widget);
}

QPointF Obstacle::getPos() {
    QGraphicsRectItem::pos();
}

QJsonObject Obstacle::toJSON() {
    QJsonObject json;
    json["x"] = pos().x();
    json["y"] = pos().y();
    json["width"] = rect().width();
    json["rotation"] = rotation();
    return json;
}

Obstacle Obstacle::fromJSON(QJsonObject &json) {
    Obstacle result;

    if (const QJsonValue v = json["width"]; v.isDouble())
        result.setRect(0, 0, v.toDouble(), v.toDouble());

    if (const QJsonValue v = json["x"]; v.isDouble())
        result.setPos(v.toDouble(), 0);

    if (const QJsonValue v = json["y"]; v.isDouble())
        result.setPos(pos().x(), v.toDouble());

    if (const QJsonValue v = json["rotation"]; v.isDouble())
        result.setRotation(v.toDouble());

    return result;
}