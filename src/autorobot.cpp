#include "autorobot.hpp"

AutoRobot::AutoRobot(QGraphicsItem *parent, qreal collisionLookAhead, Robot::RotationDirection rotationDirection, qreal moveSpeed, qreal rotationSpeed) : Robot(parent)
{
    this->collisionLookAhead = collisionLookAhead;
    this->rotationDirection = rotationDirection;
    setMoveSpeed(moveSpeed);
    setRotationSpeed(rotationSpeed);

    setRect(0, 0, 40, 40);
    setTransformOriginPoint(rect().width() / 2, rect().height() / 2);

    // Set the color of the ellipse to red
    setPen(QPen(Qt::red, 1));

    // Start moving the robot
    startMoving();
}

AutoRobot::~AutoRobot() {}

void AutoRobot::doRotationStep(RotationDirection direction) { setRotation(rotation() + rotation_speed * direction); }

bool AutoRobot::move()
{
    bool hasNotCollided = Robot::move();
    if (!hasNotCollided)
    {
        doRotationStep(rotationDirection);
    }

    return hasNotCollided;
}
