#include "autorobot.hpp"

AutoRobot::AutoRobot(QGraphicsItem *parent, qreal collisionLookAhead, Robot::RotationDirection rotationDirection, qreal moveSpeed, qreal rotationSpeed, qreal *timeConstant) : Robot(parent, timeConstant)
{
    setFlag(QGraphicsItem::ItemIsFocusable, false);

    this->collisionLookAhead = collisionLookAhead;
    this->rotationDirection = rotationDirection;
    setMoveSpeed(moveSpeed);
    setRotationSpeed(rotationSpeed);

    setRect(0, 0, 10, 10);
    setTransformOriginPoint(getRadius(), getRadius());

    // Set the color of the ellipse to red
    setPen(QPen(Qt::red, 1));

    // Start moving the robot
    startMoving();
}

AutoRobot::~AutoRobot() {}

void AutoRobot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Robot::paint(painter, option, widget);

    // Draw the collision look ahead line
    QPen pen = painter->pen();
    pen.setStyle(Qt::SolidLine);
    painter->setPen(pen);
    painter->drawLine(getRadius(), getRadius(), getRadius() * 2 + collisionLookAhead, getRadius());
}

QRectF AutoRobot::boundingRect() const
{
    const qreal radius = getRadius();
    return QRectF(0, 0, 2 * radius + collisionLookAhead, 2 * radius);
}

bool AutoRobot::willCollide(QPointF directionVector, qreal magnitude)
{
    return Robot::willCollide(directionVector, magnitude) || Robot::willCollide(directionVector, magnitude + collisionLookAhead);
}

void AutoRobot::doRotationStep(RotationDirection direction)
{
    targetAngle += rotation_speed * direction * (*timeConstant);
}

bool AutoRobot::move()
{
    bool reachedTargetAngleClockwise = rotation() >= targetAngle && rotationDirection == Robot::RotationDirection::Right;
    bool reachedTargetAngleCounterClockwise = rotation() <= targetAngle && rotationDirection == Robot::RotationDirection::Left;

    if (!reachedTargetAngleClockwise && !reachedTargetAngleCounterClockwise)
    {
        setRotation(rotation() + SMOOTH_ROTATION_SPEED * rotationDirection);
        return true;
    }

    bool hasNotCollided = Robot::move();
    if (!hasNotCollided)
    {
        doRotationStep(rotationDirection);
    }

    return hasNotCollided;
}
