/**
 * @file robot.h
 * @brief This file provides the definition of the Robot class.
 * @authors Jakub Všetečka, Tomáš Hobza
 */

#ifndef ROBOT_H
#define ROBOT_H

#include "gameobject.h"
#include <QGraphicsScene>

class Robot : public GameObject
{
public:
  Robot(QGraphicsItem *parent = nullptr, QPointF position = QPointF(0, 0), QPointF dimension = QPointF(25, 25), double angle = 0.0, double velocity = 0.0);

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
  void update() override;

  // QGraphicsItem interface overrides
  QRectF boundingRect() const override;
  QPointF pos() const;

  /**
   * @brief Returns true if the robot is colliding with something.
   *
   * @return true
   * @return false
   */
  bool checkCollisions();

  Qt::GlobalColor color = Qt::transparent;

private:
  qreal collisionLookahead = 50;
};

#endif // ROBOT_H