/**
 * @file gameobject.h
 * @brief This file provides the definition of the GameObject class.
 * @authors Jakub Všetečka, Tomáš Hobza
 */

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "angledirection.h"
#include <QJsonObject>

using namespace std;

class GameObject {
  public:
    GameObject(pair<float, float> position = pair<float, float>(-25, -25), float dimension = 25.0, double angle = 0.0, double velocity = 0.0);
    virtual ~GameObject();

    virtual void update();
    void enslaveInTime(float frameTTL);
    virtual QJsonValue toJson() const;
    static GameObject *fromJson(const QJsonObject &obj);

    bool collidesWithItem(GameObject *item);

  protected:
    enum HitboxType { CIRCLE,
                      RECTANGLE } t_hitbox;

    pair<float, float> position;
    AngleDirection angleDir;
    float dimension;
    HitboxType hitboxType = RECTANGLE;
};

#endif // GAMEOBJECT_H
