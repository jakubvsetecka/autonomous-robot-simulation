#ifndef ROBUTEK_HPP
#define ROBUTEK_HPP

#include <QGraphicsEllipseItem>
#include <QPainter>
#include <QtMath>
#include <QDebug>
#include <QGraphicsScene>

class Robutek : public QGraphicsEllipseItem
{
public:
    Robutek(QGraphicsItem *parent = nullptr) : QGraphicsEllipseItem(parent)
    {
        // Set the size of the ellipse
        setRect(0, 0, 25, 25);

        // set the origin of the ellipse to the center
        setTransformOriginPoint(rect().width() / 2, rect().height() / 2);
    }

    // Override the paint method to draw a line showing the direction of the robot
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override
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
    void setPos(const QPointF &pos)
    {
        QGraphicsItem::setPos(pos - QPointF(rect().width() / 2, rect().height() / 2));
    }

    // Overload setPos to accept x and y coordinates
    void setPos(qreal x, qreal y)
    {
        setPos(QPointF(x, y));
    }

    // Override pos to adjust to center-based positioning
    QPointF pos() { return QGraphicsItem::pos() + QPointF(rect().width() / 2, rect().height() / 2); }

    void setMoveSpeed(qreal speed) { this->move_speed = speed; }
    qreal getMoveSpeed() { return move_speed; }

    void setRotationSpeed(qreal speed) { this->rotation_speed = speed; }
    qreal getRotationSpeed() { return rotation_speed; }

    void move()
    {
        setRotation(rotation() + rotation_speed); // Rotate the robot

        qreal angle = rotation(); // Use rotation as the direction
        qreal dx = move_speed * qCos(qDegreesToRadians(angle));
        qreal dy = move_speed * qSin(qDegreesToRadians(angle));

        // Check scene boundaries
        if (scene() != nullptr)
        {
            // Get the scene rectangle with the robot's size taken into account (center-based positioning, so the margin is half the size of the robot)
            QRectF sceneRect = scene()->sceneRect().adjusted(rect().width() / 2, rect().height() / 2, -rect().width() / 2, -rect().height() / 2);
            if (!sceneRect.contains(pos() + QPointF(dx, dy)))
            {
                // If the new position is outside the scene, don't move
                return;
            }
        }

        moveBy(dx, dy);
    }

    void update()
    {
        move();
    }

private:
    qreal move_speed = 0;     // The speed of the robot
    qreal rotation_speed = 0; // The speed of the rotation of the robot
};

#endif // ROBUTEK_HPP