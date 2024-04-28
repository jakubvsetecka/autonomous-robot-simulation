#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include <QGraphicsRectItem>
#include <QBrush>

class Obstacle : public QGraphicsRectItem
{
public:
    Obstacle(QGraphicsItem *parent = nullptr) : QGraphicsRectItem(parent)
    {
        setRect(0, 0, 40, 40);
        setTransformOriginPoint(rect().width() / 2, rect().height() / 2);
        QBrush brush(Qt::blue);
        setBrush(brush);
    }

    ~Obstacle() {}

    // TODO: Implement the obstacle's rotation
};

#endif // OBSTACLE_HPP