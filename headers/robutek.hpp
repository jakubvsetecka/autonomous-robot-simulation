#ifndef ROBUTEK_HPP
#define ROBUTEK_HPP

#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include "angledirection.h"

class Robutek : public QGraphicsRectItem
{
public:
    Robutek()
    {
        setPos(100, 100);
        setTransformOriginPoint(boundingRect().center());
    }
    ~Robutek() {}

    AngleDirection angleDir = AngleDirection(0.0, 1.0);

    void rotate(double angle)
    {
        angleDir.rotate(angle);
        setRotation(angleDir.getAngle());
    }

private:
};

#endif // ROBUTEK_HPP