/**
 * @file robot.hpp
 * @brief This file contains the declaration of the Robot class.
 * @details It is a subclass of the QGraphicsEllipseItem class and represents a robot in the simulation.
 * @authors Tomáš Hobza, Jakub Všetečka
 * @date 02.05.2024
 */

#ifndef ROBOT_HPP
#define ROBOT_HPP

#include "gameobject.hpp"
#include <QDebug>
#include <QFocusEvent>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QObject>
#include <QPainter>
#include <QPointF>
#include <QtMath>

#define BODY_COLLISION_MARGIN 1

/**
 * @brief A class to represent a robot in the simulation. By default, the robot is a circle with a line drawn to represent its direction.
 */
class Robot : public QObject, public QGraphicsEllipseItem, public GameObject {
    Q_OBJECT

  public:
    /**
     * @brief Enum to represent the direction of rotation of the robot.
     */
    enum RotationDirection {
        Left = -1, // Counter-clockwise
        None = 0,  // No rotation
        Right = 1  // Clockwise
    };

    enum { Type = QGraphicsItem::UserType + 1 };

    Robot(QGraphicsItem *parent = nullptr, qreal *timeConstant = nullptr);

    /** Override the paint method to draw a line showing the direction of the robot */
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    /** Override setPos to adjust to center-based positioning */
    void setPos(const QPointF &pos);

    /** Overload setPos to accept x and y coordinates */
    void setPos(qreal x, qreal y) override;

    /* Override the boundingRect method to adjust the bounding rectangle */
    virtual QRectF boundingRect() const override;

    /** Override pos to adjust to center-based positioning */
    QPointF pos();

    qreal getRadius() const;

    /**
     * @brief Set the move speed of the robot.
     *
     * @param speed
     */
    void setMoveSpeed(qreal speed);

    /**
     * @brief Get the move speed of the robot.
     *
     * @return qreal
     */
    qreal getMoveSpeed();

    /**
     * @brief Set the rotation speed of the robot.
     *
     * @param speed
     */
    void setRotationSpeed(qreal speed);

    /**
     * @brief Get the rotation speed of the robot.
     *
     * @return qreal
     */
    qreal getRotationSpeed();

    /**
     * @brief Allow the robot to be moved by setting the isMoving flag to true.
     */
    void startMoving();

    /**
     * @brief Stop the robot from moving by setting the isMoving flag to false.
     */
    void stopMoving();

    /**
     * @brief Start rotating the robot in the given direction.
     *
     * @param direction
     */
    void startRotating(RotationDirection direction);

    /**
     * @brief Stop the robot from rotating by setting the isRotating flag to None.
     */
    void stopRotating();

    /**
     * @brief Get the direction vector of the robot.
     *
     * @return `QPointF` - Normalized vector representing the direction of the robot on the x and y axes
     */
    QPointF getDirectionVector();

    /**
     * @brief Check if the robot will collide with any other item in the scene or the scene boundaries if it moves by the given vector.
     *
     * @param moveVector The vector by which the robot will move
     * @param allowAnticollision Flag to indicate if anticollision is allowed
     * @return `true` - if the robot will collide; `false` - if the robot will not collide
     */
    virtual bool willCollide(QPointF directionVector, qreal magnitude, bool allowAnticollision = false);

    /**
     * @brief Move the robot based on its current direction and speed. Returns true if the robot moved, false if it didn't (e.g. if it hit a boundary).
     *
     * @return true
     * @return false
     */
    virtual bool move();

    int type() const override { return Type; }

    QPointF getPos() override;
    virtual QJsonObject toJSON() override;
    static Robot *fromJSON(const QJsonObject &object, qreal *timeConstant);

    inline void toggleActive() {
        active = !active;
        active ? setBrush(QBrush(Qt::lightGray)) : setBrush(QBrush(Qt::transparent));
    }

    inline bool isActive() { return active; }

    qreal getAngle() { return rotation(); }

    void setRadius(qreal radius);

    QPointF getCenter() override { return boundingRect().center(); }

    qreal rotation() override {
        return QGraphicsEllipseItem::rotation();
    }

    void setRotation(qreal angle) override {
        QGraphicsEllipseItem::setRotation(angle);
    }

  signals:
    void paramsUpdated();

  protected:
    /** @brief The speed of the robot */
    qreal move_speed = 1;
    /** @brief The speed of the rotation of the robot */
    qreal rotation_speed = 1;

    /** @brief Flag to indicate if the robot is moving */
    bool isMoving = false;
    /** @brief Flag to indicate the direction of rotation */
    RotationDirection isRotating = RotationDirection::None;

    qreal *timeConstant = nullptr;

    void keyReleaseEvent(QKeyEvent *event);
    void keyPressEvent(QKeyEvent *event);

  private:
    bool active = false;
};

#endif // ROBOT_HPP