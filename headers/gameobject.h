/**
 * @file gameobject.h
 * @brief This file provides the definition of the GameObject class.
 * @authors Jakub Všetečka, Tomáš Hobza
 */

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "angledirection.h"

class enum ObjectType {
    ROBOT,
    OBSTACLE
};

class GameObject {
  public:
    GameObject(QPointF position = QPointF(-25, -25), QPointF dimension = QPointF(25, 25), double angle = 0.0, double velocity = 0.0);
    virtual ~GameObject();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    virtual void update();
    virtual QJsonValue toJson() const;
    static GameObject *fromJson(const QJsonObject &obj);

  protected:
    std::pair<float, float> position;
    AngleDirection angleDir;
    float dimension;
};

#endif // GAMEOBJECT_H
