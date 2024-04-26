/**
 * @file gameobject.h
 * @brief This file provides the definition of the GameObject class.
 * @authors Jakub Všetečka, Tomáš Hobza
 */

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "angledirection.h"
#include <QGraphicsItem>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QPainter>

class GameObject : public QGraphicsItem {
  public:
    GameObject(QGraphicsItem *parent = nullptr, QPointF position = QPointF(-25, -25), QPointF dimension = QPointF(25, 25), double angle = 0.0, double velocity = 0.0)
        : QGraphicsItem(parent), position(position), angleDir(angle, velocity), dimension(dimension) {
        setTransformOriginPoint(boundingRect().center());
    }

    virtual ~GameObject() {}

    QRectF boundingRect() const override {
        return QRectF(position.x(), position.y(), dimension.x(), dimension.y());
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override {
        QBrush brush(Qt::CrossPattern);
        painter->setBrush(brush);
        painter->drawRect(boundingRect());
    }

    virtual void update() {
        moveBy(angleDir.getX(), angleDir.getY());
        setRotation(angleDir.angle);
    }

    virtual QJsonValue toJson() const {
        // Convert object to JSON
    }

    static GameObject *fromJson(const QJsonObject &obj) {
        // Create object from JSON

    } // Static method returning a pointer

  protected:
    QPointF position;
    AngleDirection angleDir;
    QPointF dimension;
};

#endif // GAMEOBJECT_H