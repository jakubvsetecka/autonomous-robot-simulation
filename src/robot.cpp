#include "robot.hpp"

Robot::Robot(QGraphicsItem *parent) : QGraphicsEllipseItem(parent)
{
    // Set the size of the ellipse
    setRect(0, 0, 25, 25);

    // set the origin of the ellipse to the center
    setTransformOriginPoint(rect().width() / 2, rect().height() / 2);
}

void Robot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // Call the base class paint to draw the ellipse
    QGraphicsEllipseItem::paint(painter, option, widget);

    // Define the line's style
    QPen pen(Qt::black, 1); // Set the color and width of the line
    painter->setPen(pen);

    // Draw a line through the center of the ellipse
    qreal centerX = rect().width() / 2;
    qreal centerY = rect().height() / 2;
    painter->drawLine(centerX, centerY, rect().width(), centerY);
}

// Override setPos to adjust to center-based positioning
void Robot::setPos(const QPointF &pos)
{
    QGraphicsItem::setPos(pos - QPointF(rect().width() / 2, rect().height() / 2));
}

// Overload setPos to accept x and y coordinates
void Robot::setPos(qreal x, qreal y)
{
    setPos(QPointF(x, y));
}

// Override pos to adjust to center-based positioning
QPointF Robot::pos() { return QGraphicsItem::pos() + QPointF(rect().width() / 2, rect().height() / 2); }

void Robot::setMoveSpeed(qreal speed) { this->move_speed = speed; }
qreal Robot::getMoveSpeed() { return move_speed; }

void Robot::setRotationSpeed(qreal speed) { this->rotation_speed = speed; }
qreal Robot::getRotationSpeed() { return rotation_speed; }

void Robot::startMoving() { isMoving = true; }
void Robot::stopMoving() { isMoving = false; }

void Robot::startRotating(RotationDirection direction) { isRotating = direction; }
void Robot::stopRotating() { isRotating = RotationDirection::None; }

QPointF Robot::getDirectionVector()
{
    qreal angle = rotation();
    qreal dx = qCos(qDegreesToRadians(angle));
    qreal dy = qSin(qDegreesToRadians(angle));

    return QPointF(dx, dy);
}

bool Robot::willCollide(QPointF moveVector)
{
    if (scene() != nullptr)
    {
        qreal radius = rect().width() / 2;   // Radius of the robot
        QPointF newPos = pos() + moveVector; // New position center after the intended move

        // Ensure new position stays within the scene boundaries, accounting for the robot's radius
        QRectF sceneRect = scene()->sceneRect().adjusted(radius, radius, -radius, -radius);
        if (!sceneRect.contains(newPos))
        {
            return true; // Collision with scene boundaries
        }

        // Check for collisions with other items in the scene
        QList<QGraphicsItem *> potentialCollisions = scene()->items(QRectF(newPos.x() - radius, newPos.y() - radius, 2 * radius, 2 * radius));
        for (QGraphicsItem *item : potentialCollisions)
        {
            if (item != this)
            {
                QRectF itemRect = item->sceneBoundingRect();
                qreal closestX = qMax(itemRect.left(), qMin(newPos.x(), itemRect.right()));
                qreal closestY = qMax(itemRect.top(), qMin(newPos.y(), itemRect.bottom()));
                qreal distanceX = newPos.x() - closestX;
                qreal distanceY = newPos.y() - closestY;

                // Calculate distance from closest point on the item's bounding rectangle to the new center position of the robot
                if (distanceX * distanceX + distanceY * distanceY < radius * radius)
                {
                    return true; // Collision detected
                }
            }
        }
    }

    return false;
}

bool Robot::move()
{
    if (isRotating != RotationDirection::None)
    {
        setRotation(rotation() + rotation_speed * isRotating); // Rotate the robot

        return true; // Don't move if rotating
    }

    if (isMoving)
    {
        QPointF moveVector = getDirectionVector() * move_speed;

        if (willCollide(moveVector))
        {
            return false;
        }

        moveBy(moveVector.x(), moveVector.y());
    }

    return true;
}