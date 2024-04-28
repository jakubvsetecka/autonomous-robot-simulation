#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include <QBrush>
#include <QGraphicsRectItem>

class Obstacle : public QGraphicsRectItem {
  public:
    Obstacle(QGraphicsItem *parent = nullptr);

    ~Obstacle();
};

#endif // OBSTACLE_HPP