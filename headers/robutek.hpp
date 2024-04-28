#ifndef ROBUTEK_HPP
#define ROBUTEK_HPP

#include "simulationengine.hpp"
#include <QGraphicsEllipseItem>
#include <QPainter>
#include <QtMath>

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

    void setSpeed(qreal speed) { this->speed = speed; }
    qreal getSpeed() { return speed; }

    void move(qreal simulationSpeed = 1.0)
    {
        qreal angle = rotation(); // Use rotation as the direction
        qreal dx = speed * qCos(qDegreesToRadians(angle)) * simulationSpeed;
        qreal dy = speed * qSin(qDegreesToRadians(angle)) * simulationSpeed;
        moveBy(dx, dy);
    }

private:
    qreal speed = 0.1; // The speed of the robot
};

#endif // ROBUTEK_HPP