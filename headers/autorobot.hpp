#ifndef AUTOROBOT_HPP
#define AUTOROBOT_HPP

#include "robot.hpp"

class AutoRobot : public Robot
{
public:
    AutoRobot(QGraphicsItem *parent = nullptr, qreal collisionLookAhead = 10, Robot::RotationDirection rotationDirection = Robot::RotationDirection::Right, qreal moveSpeed = 1, qreal rotationSpeed = 1);
    ~AutoRobot();

    void doRotationStep(RotationDirection direction);

    bool move();

protected:
    qreal collisionLookAhead = 10;
    Robot::RotationDirection rotationDirection = Robot::RotationDirection::Right;
};

#endif // AUTOROBOT_HPP