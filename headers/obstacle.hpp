/**
 * @file obstacle.hpp
 * @brief This file contains the declaration of the Obstacle class.
 * @details It is a subclass of the QGraphicsRectItem class and represents an obstacle in the game.
 * @authors Tomáš Hobza, Jakub Všetečka
 * @date 02.05.2024
 */

#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include "gameobject.hpp"
#include <QBrush>
#include <QGraphicsRectItem>
#include <QJsonObject>
#include <QObject>

/**
 * @class Obstacle
 * @brief A class to represent an obstacle.
 * @details This class inherits from QGraphicsRectItem and GameObject. It represents an obstacle in a game.
 */
class Obstacle : public QObject, public QGraphicsRectItem, public GameObject {
    Q_OBJECT

  public:
    /**
     * @brief Default constructor.
     * @param parent The parent QGraphicsItem.
     */
    Obstacle(QGraphicsItem *parent = nullptr);

    /**
     * @brief Copy constructor.
     * @param Obstacle The Obstacle object to copy.
     */
    Obstacle(const Obstacle &)
        : QGraphicsRectItem() {}

    /**
     * @brief Destructor.
     */
    ~Obstacle();

    /**
     * @brief Set the position of the obstacle.
     * @param x The x-coordinate of the position.
     * @param y The y-coordinate of the position.
     */
    void setPos(qreal x, qreal y) override;

    void setRotation(qreal angle) override;

    /**
     * @brief Paint the obstacle.
     * @param painter Pointer to the QPainter object.
     * @param option Pointer to the QStyleOptionGraphicsItem object.
     * @param widget Pointer to the QWidget object.
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    /**
     * @brief Get the position of the obstacle.
     * @return The position of the obstacle as a QPointF object.
     */
    QPointF getPos() override;

    /**
     * @brief Convert the obstacle to a JSON object.
     * @return The obstacle as a QJsonObject.
     */
    QJsonObject toJSON() override;

    /**
     * @brief Create an Obstacle object from a JSON object.
     * @param json The QJsonObject to convert.
     * @return A pointer to the created Obstacle object.
     */
    static Obstacle *fromJSON(const QJsonObject &json);

  signals:
    void paramsUpdated();
};

#endif // OBSTACLE_HPP