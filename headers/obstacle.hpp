#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include "gameobject.hpp"
#include <QBrush>
#include <QGraphicsRectItem>

class Obstacle : public QGraphicsRectItem, public GameObject {
  public:
    Obstacle(QGraphicsItem *parent = nullptr);

    ~Obstacle();

    void setPos(qreal x, qreal y) override;
};

#endif // OBSTACLE_HPP