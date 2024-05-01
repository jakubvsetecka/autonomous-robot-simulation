#include "autorobot.hpp"

AutoRobot::AutoRobot(QGraphicsItem *parent, qreal size, qreal collisionLookAhead, Robot::RotationDirection rotationDirection, qreal moveSpeed, qreal rotationSpeed, qreal *timeConstant)
    : Robot(parent, timeConstant) {
    setFlag(QGraphicsItem::ItemIsFocusable, false);

    this->collisionLookAhead = collisionLookAhead;
    this->rotationDirection = rotationDirection;
    setMoveSpeed(moveSpeed);
    setRotationSpeed(rotationSpeed);

    setRect(0, 0, size, size);
    setTransformOriginPoint(getRadius(), getRadius());

    // Set the color of the ellipse to red
    setPen(QPen(Qt::red, 1));

    // Start moving the robot
    startMoving();
}

AutoRobot::~AutoRobot() {}

void AutoRobot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Robot::paint(painter, option, widget);

    // Draw the collision look ahead line
    QPen pen = painter->pen();
    pen.setStyle(Qt::SolidLine);
    painter->setPen(pen);
    painter->drawLine(getRadius(), getRadius(), getRadius() * 2 + collisionLookAhead, getRadius());
}

QRectF AutoRobot::boundingRect() const {
    const qreal radius = getRadius();
    return QRectF(0, 0, 2 * radius + collisionLookAhead, 2 * radius);
}

bool AutoRobot::willCollide(QPointF directionVector, qreal magnitude, bool allowAnticollision) {
    return Robot::willCollide(directionVector, magnitude, allowAnticollision) || (collisionLookAhead > 0 && Robot::willCollide(directionVector, magnitude + collisionLookAhead, false));
}

void AutoRobot::doRotationStep(RotationDirection direction) {
    targetAngle += rotation_speed * direction;
}

bool AutoRobot::move() {
    bool reachedTargetAngleClockwise = rotation() >= targetAngle && rotationDirection == Robot::RotationDirection::Right;
    bool reachedTargetAngleCounterClockwise = rotation() <= targetAngle && rotationDirection == Robot::RotationDirection::Left;

    if (!reachedTargetAngleClockwise && !reachedTargetAngleCounterClockwise) {
        setRotation(rotation() + SMOOTH_ROTATION_SPEED * rotationDirection * (*timeConstant));
        return true;
    }

    bool hasNotCollided = Robot::move();
    if (!hasNotCollided) {
        doRotationStep(rotationDirection);
    }

    return hasNotCollided;
}

QJsonObject AutoRobot::toJSON() {
    QJsonObject json = Robot::toJSON();
    json["collisionLookAhead"] = collisionLookAhead;
    json["rotationDirection"] = rotationDirection;
    json["targetAngle"] = targetAngle;
    json["x"] = pos().x();
    json["y"] = pos().y();
    json["rotation"] = rotation();
    json["radius"] = getRadius();
    json["moveSpeed"] = getMoveSpeed();
    json["rotationSpeed"] = getRotationSpeed();
    json["isMoving"] = isMoving;
    return json;
}

AutoRobot *AutoRobot::fromJSON(const QJsonObject &object, qreal *timeConstant) {
    AutoRobot *result = new AutoRobot();
    QPointF pos;

    if (const QJsonValue v = object["collisionLookAhead"]; v.isDouble())
        result->setCollisionLookAhead(v.toDouble());

    if (const QJsonValue v = object["rotationDirection"]; v.isDouble())
        result->setRotationDirection(static_cast<RotationDirection>(v.toInt()));

    if (const QJsonValue v = object["targetAngle"]; v.isDouble())
        result->setTargetAngle(v.toDouble());

    if (const QJsonValue v = object["x"]; v.isDouble())
        pos.setX(v.toDouble());

    if (const QJsonValue v = object["y"]; v.isDouble())
        pos.setY(v.toDouble());

    if (const QJsonValue v = object["rotation"]; v.isDouble())
        result->setRotation(v.toDouble());

    if (const QJsonValue v = object["radius"]; v.isDouble()) {
        result->setRect(0, 0, v.toDouble() * 2, v.toDouble() * 2);
    }

    if (const QJsonValue v = object["moveSpeed"]; v.isDouble())
        result->setMoveSpeed(v.toDouble());

    if (const QJsonValue v = object["rotationSpeed"]; v.isDouble())
        result->setRotationSpeed(v.toDouble());

    if (const QJsonValue v = object["isMoving"]; v.isBool())
        result->isMoving = v.toBool();

    result->timeConstant = timeConstant;
    result->setPos(pos); // Must be set using setPos() to use the center of the robot as the position

    return result;
}