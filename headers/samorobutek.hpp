#ifndef SAMOROBUTEK_HPP
#define SAMOROBUTEK_HPP

#include "robutek.hpp"

class Samorobutek : public Robutek
{
public:
    Samorobutek(QGraphicsItem *parent = nullptr, qreal collisionLookAhead = 10) : Robutek(parent)
    {
        this->collisionLookAhead = collisionLookAhead;

        setRect(0, 0, 40, 40);
        setTransformOriginPoint(rect().width() / 2, rect().height() / 2);

        // Set the color of the ellipse to red
        setPen(QPen(Qt::red, 1));

        // Start moving the robot
        startMoving();
    }

    void doRotationStep(RotationDirection direction) { setRotation(rotation() + rotation_speed * direction); }

    bool move()
    {
        bool hasNotCollided = Robutek::move();
        if (!hasNotCollided)
        {
            doRotationStep(Robutek::RotationDirection::Right);
        }

        return hasNotCollided;
    }

    ~Samorobutek() {}

protected:
    qreal collisionLookAhead = 10;
};

#endif // SAMOROBUTEK_HPP