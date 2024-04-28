#include "autorobot.hpp"

AutoRobot::AutoRobot(QGraphicsItem *parent, qreal collisionLookAhead, Robot::RotationDirection rotationDirection, qreal moveSpeed, qreal rotationSpeed) : Robot(parent)
{
    setFlag(QGraphicsItem::ItemIsFocusable, true);

    this->collisionLookAhead = collisionLookAhead;
    this->rotationDirection = rotationDirection;
    setMoveSpeed(moveSpeed);
    setRotationSpeed(rotationSpeed);

    setRect(0, 0, 40, 40);
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

    // // Draw the boundingRect
    QPen pen = painter->pen();
    // pen.setStyle(Qt::DashLine);
    // painter->setPen(pen);
    // painter->drawRect(rect());

    // Draw the collision look ahead line
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

void AutoRobot::focusInEvent(QFocusEvent *event) {}
void AutoRobot::focusOutEvent(QFocusEvent *event) {}
