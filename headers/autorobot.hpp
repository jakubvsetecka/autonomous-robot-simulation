#ifndef AUTOROBOT_HPP
#define AUTOROBOT_HPP

#include "robot.hpp"

class AutoRobot : public Robot
{
public:
    AutoRobot(QGraphicsItem *parent = nullptr, qreal collisionLookAhead = 10);
    ~AutoRobot();

    void doRotationStep(RotationDirection direction);

    bool move();

protected:
    qreal collisionLookAhead = 10;
};

#endif // AUTOROBOT_HPP