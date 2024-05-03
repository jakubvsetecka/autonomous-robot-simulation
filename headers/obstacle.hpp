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
     * @return void
     */
    Obstacle(QGraphicsItem *parent = nullptr);

    /**
     * @brief Copy constructor.
     * @param Obstacle The Obstacle object to copy.
     * @return void
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
     * @return void
     */
    void setPos(qreal x, qreal y) override;

    /**
     * @brief Set the rotation of the obstacle.
     * @param angle The angle of the rotation.
     * @return void
     */
    void setRotation(qreal angle) override;

    /**
     * @brief Get the rotation of the obstacle.
     * @return The rotation of the obstacle as a qreal.
     */
    qreal rotation() override { return QGraphicsRectItem::rotation(); }

    /**
     * @brief Get the center of the obstacle.
     * @return The center of the obstacle as a QPointF.
     */
    QPointF getCenter() override { return boundingRect().center(); }

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
    /**
     * @brief Signal emitted when the parameters of the obstacle are updated.
     * @return void
     */
    void paramsUpdated();
};

#endif // OBSTACLE_HPP