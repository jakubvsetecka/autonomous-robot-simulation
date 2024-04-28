#ifndef SAMOROBUTEK_HPP
#define SAMOROBUTEK_HPP

#include "robutek.hpp"

class Samorobutek : public Robutek
{
public:
    Samorobutek(QGraphicsItem *parent = nullptr, qreal collisionLookAhead = 10) : Robutek(parent)
    {
        this->collisionLookAhead = collisionLookAhead;

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