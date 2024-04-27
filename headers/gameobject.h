/**
 * @file gameobject.h
 * @brief This file provides the definition of the GameObject class.
 * @authors Jakub Všetečka, Tomáš Hobza
 */

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "angledirection.h"
#include <QGraphicsItem>
#include <QPainter>
#include <QPointF>

class GameObject : public QGraphicsItem
{
public:
  GameObject(QGraphicsItem *parent = nullptr, QPointF position = QPointF(-25, -25), QPointF dimension = QPointF(25, 25), double angle = 0.0, double velocity = 0.0);
  virtual ~GameObject();

  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
  virtual void update();
  virtual QJsonValue toJson() const;
  static GameObject *fromJson(const QJsonObject &obj);
  void enslaveToTime(float frameTTL);
  AngleDirection angleDir;

protected:
  QPointF dimension;
};

#endif // GAMEOBJECT_H
