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

    /**
     * @brief Default constructor.
     * @param parent The parent QGraphicsItem.
     * @param timeConstant The time constant of the simulation.
     * @return void
     * @details The time constant is used to calculate the speed of the robot.
    */
    Robot(QGraphicsItem *parent = nullptr, qreal *timeConstant = nullptr);

    ~Robot();

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

    /**
     * @brief Get the type of the robot.
     * @return int
     */
    int type() const override { return Type; }

    /**
     * @brief Get the position of the robot.
     * @return QPointF
     */
    QPointF getPos() override;

    /**
     * @brief Convert the robot to a JSON object.
     * @return QJsonObject
     */
    virtual QJsonObject toJSON() override;

    /**
     * @brief Create a Robot object from a JSON object.
     * @param object The JSON object.
     * @param timeConstant The time constant of the simulation.
     * @return Robot*
     */
    static Robot *fromJSON(const QJsonObject &object, qreal *timeConstant);

    /**
     * @brief Toggle the active state of the robot.
     * @details If the robot is active, it will be drawn with a light gray fill. If it is inactive, it will be drawn with a transparent fill.
     * @return void
     */
    inline void toggleActive() {
        active = !active;
        active ? setBrush(QBrush(Qt::lightGray)) : setBrush(QBrush(Qt::transparent));
    }

    /**
     * @brief Check if the robot is active.
     * @return bool
     */
    inline bool isActive() { return active; }

    /**
     * @brief Get the angle of the robot.
     * @return qreal
     */
    qreal getAngle() { return rotation(); }

    /**
     * @brief Set the angle of the robot.
     * @param angle The angle to set.
     * @return void
     */
    void setRadius(qreal radius);

    /**
     * @brief Get the center of the robot.
     * @return QPointF
     */
    QPointF getCenter() override { return boundingRect().center(); }

    /**
     * @brief Get the time constant of the simulation.
     * @return qreal
     */
    qreal rotation() override {
        return QGraphicsEllipseItem::rotation();
    }

    /**
     * @brief Set the rotation of the robot.
     * @param angle The angle to set.
     * @return void
     */
    void setRotation(qreal angle) override {
        QGraphicsEllipseItem::setRotation(angle);
    }

  signals:

    /**
     * @brief Signal emitted when the parameters of the robot are updated.
     * @return void
    */
    void paramsUpdated();

    /**
     * @brief Signal emitted when the robot is removed.
     * @return void
     */
    void robotSepuku();

  protected:
    /** @brief The speed of the robot */
    qreal move_speed = 1;
    /** @brief The speed of the rotation of the robot */
    qreal rotation_speed = 1;

    /** @brief Flag to indicate if the robot is moving */
    bool isMoving = false;

    /** @brief Flag to indicate the direction of rotation */
    RotationDirection isRotating = RotationDirection::None;

    /** @brief The time constant of the simulation */
    qreal *timeConstant = nullptr;

    /** @brief The radius of the robot */
    void keyReleaseEvent(QKeyEvent *event);

    /**
     * @brief Overridden keyPressEvent method.
     * @details This method is called when a key is pressed while the robot is focused.
     * @param event The key event.
     * @return void
     */
    void keyPressEvent(QKeyEvent *event);

  private:
    /** @brief Flag to indicate if the robot is active */
    bool active = false;
};

#endif // ROBOT_HPP