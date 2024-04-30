#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include "gameobject.hpp"
#include <QBrush>
#include <QGraphicsRectItem>
#include <QJsonObject>

class Obstacle : public QGraphicsRectItem, public GameObject {
  public:
    Obstacle(QGraphicsItem *parent = nullptr);

    Obstacle(const Obstacle &)
        : QGraphicsRectItem() {}

    ~Obstacle();

    void setPos(qreal x, qreal y) override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QPointF getPos() override;

    QJsonObject toJSON();
    Obstacle fromJSON(QJsonObject &json);
};

#endif // OBSTACLE_HPP