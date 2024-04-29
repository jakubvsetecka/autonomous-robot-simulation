

#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <QGraphicsItem>

class GameObject {
  public:
    GameObject() = default;
    ~GameObject() = default;

    virtual void setPos(qreal x, qreal y) = 0;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) = 0;
    virtual QPointF getPos() = 0;
};

#endif // GAMEOBJECT_HPP