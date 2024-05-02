#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include "gameobject.hpp"
#include <QBrush>
#include <QGraphicsRectItem>
#include <QJsonObject>

/**
 * @class Obstacle
 * @brief A class to represent an obstacle.
 * @details This class inherits from QGraphicsRectItem and GameObject. It represents an obstacle in a game.
 */
class Obstacle : public QGraphicsRectItem, public GameObject {
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
};

#endif // OBSTACLE_HPP