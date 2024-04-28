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