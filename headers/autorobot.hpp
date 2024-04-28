#ifndef AUTOROBOT_HPP
#define AUTOROBOT_HPP

#include "robot.hpp"

class AutoRobot : public Robot
{
public:
    AutoRobot(QGraphicsItem *parent = nullptr, qreal collisionLookAhead = 10, Robot::RotationDirection rotationDirection = Robot::RotationDirection::Right, qreal moveSpeed = 1, qreal rotationSpeed = 1);
    ~AutoRobot();

    /** Override the paint method to draw a line showing the direction of the robot */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    /* Override the boundingRect method to adjust the bounding rectangle */
    QRectF boundingRect() const override;

    bool willCollide(QPointF directionVector, qreal magnitude) override;

    void doRotationStep(RotationDirection direction);

    bool move() override;

protected:
    qreal collisionLookAhead = 0;
    Robot::RotationDirection rotationDirection = Robot::RotationDirection::Right;
};

#endif // AUTOROBOT_HPP