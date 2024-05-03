/**
 * @file autorobot.hpp
 * @brief This file contains the declaration of the AutoRobot class.
 * @details It is a subclass of the Robot class and represents an autonomous robot.
 * @authors Tomáš Hobza, Jakub Všetečka
 * @date 02.05.2024
 */

#ifndef AUTOROBOT_HPP
#define AUTOROBOT_HPP

#include "robot.hpp"
#include <QObject>

#define SMOOTH_ROTATION_SPEED 0.25

/**
 * @class AutoRobot
 * @brief A class to represent an autonomous robot.
 * @details This class inherits from Robot and provides functionalities for an autonomous robot.
 * @see Robot
 */
class AutoRobot : public QObject, public Robot {
    Q_OBJECT

  public:
    enum { Type = QGraphicsItem::UserType + 2 };

    /**
     * @brief Constructor for AutoRobot.
     * @param parent The parent QGraphicsItem.
     * @param size The size of the robot.
     * @param collisionLookAhead The distance the robot looks ahead for collisions.
     * @param rotationDirection The initial rotation direction of the robot.
     * @param moveSpeed The movement speed of the robot.
     * @param rotationSpeed The rotation speed of the robot.
     * @param timeConstant A pointer to the time constant.
     */
    AutoRobot(QGraphicsItem *parent = nullptr, qreal size = 50, qreal collisionLookAhead = 10, Robot::RotationDirection rotationDirection = Robot::RotationDirection::Right, qreal moveSpeed = 1, qreal rotationSpeed = 1, qreal *timeConstant = nullptr);
    ~AutoRobot();

    /** Override the paint method to draw a line showing the direction of the robot */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    /* Override the boundingRect method to adjust the bounding rectangle */
    QRectF boundingRect() const override;

    bool willCollide(QPointF directionVector, qreal magnitude, bool allowAnticollision) override;

    void doRotationStep(RotationDirection direction);

    bool move() override;

    /**
     * @brief Get the type of the object
     * @return int The type of the object
     */
    int type() const override { return Type; }

    /**
     * @brief Set the look ahead distance for collision detection
     * @param lookAhead The look ahead distance
     * @return void
     */
    void setCollisionLookAhead(qreal lookAhead) { collisionLookAhead = lookAhead; }

    /**
     * @brief Get the look ahead distance for collision detection
     * @return qreal The look ahead distance
     */
    qreal getCollisionLookAhead() { return collisionLookAhead; }

    /**
     * @brief Set the rotation direction of the robot
     * @param direction The rotation direction
     * @return void
     */
    void setRotationDirection(RotationDirection direction) { rotationDirection = direction; }

    /**
     * @brief Get the rotation direction of the robot
     * @return RotationDirection The rotation direction
     */
    RotationDirection getRotationDirection() { return rotationDirection; }

    /**
     * @brief Set the target angle of the robot
     * @param angle The target angle
     * @return void
     */
    void setTargetAngle(qreal angle) { targetAngle = angle; }

    /**
     * @brief Get the target angle of the robot
     * @return qreal The target angle
     */
    qreal getTargetAngle() { return targetAngle; }

    /**
     * @brief Get the JSON representation of the object
     * @return QJsonObject The JSON representation of the object
     */
    QJsonObject toJSON() override;

    /**
     * @brief Create an AutoRobot object from a JSON object
     * @param object The JSON object to create the AutoRobot object from
     * @param timeConstant The time constant of the robot
     * @return AutoRobot* The AutoRobot object created from the JSON object
     */
    static AutoRobot *fromJSON(const QJsonObject &object, qreal *timeConstant);

  signals:
    void paramsUpdated();

  protected:
    qreal collisionLookAhead = 0;
    qreal targetAngle = 0;
    Robot::RotationDirection rotationDirection = Robot::RotationDirection::Right;
};

#endif // AUTOROBOT_HPP