/**
 * @file gameobject.hpp
 * @brief This file contains the declaration of the GameObject class.
 * @details It is an abstract class that represents a game object in the simulation.
 * @authors Tomáš Hobza, Jakub Všetečka
 * @date 02.05.2024
 */

#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <QGraphicsItem>
#include <QJsonObject>

/**
 * @class GameObject
 * @brief A class to represent a game object in the simulation.
 * @details This class provides an interface for creating and managing game objects.
 */
class GameObject {
  public:
    GameObject() = default;
    ~GameObject() = default;

    /**
     * @brief Set the position of the game object.
     * @param x
     * @param y
     * @return void
     */
    virtual void setPos(qreal x, qreal y) = 0;

    /**
     * @brief Paint the game object.
     * @param painter
     * @param option
     * @param widget
     * @return void
     */
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) = 0;

    /**
     * @brief Get the position of the game object.
     * @return QPointF
     */
    virtual QPointF getPos() = 0;

    /**
     * @brief Convert the game object to a JSON object.
     * @return QJsonObject
     */
    virtual QJsonObject toJSON() = 0;
};

#endif // GAMEOBJECT_HPP