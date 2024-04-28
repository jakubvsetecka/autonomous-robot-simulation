

#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <QGraphicsItem>

class GameObject {
  public:
    GameObject() = default;
    ~GameObject() = default;

    virtual void setPos(qreal x, qreal y) = 0;
};

#endif // GAMEOBJECT_HPP