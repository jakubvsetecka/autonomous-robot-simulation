/**
 * @file angledirection.h
 * @brief This file provides the definition of the AngleDirection class.
 * @authors Jakub Všetečka, Tomáš Hobza
 */

#ifndef ANGLEDIRECTION_H
#define ANGLEDIRECTION_H

#include <cmath>

class AngleDirection
{
public:
    double angle;     // Angle in degrees or radians
    double magnitude; // Magnitude of the vector

    // Constructor
    AngleDirection(double angle = 0.0, double magnitude = 0.0)
        : magnitude(magnitude)
    {
        setAngle(angle);
    }

    // Setters and getters
    void setAngle(double angle)
    {
        this->angle = angle * M_PI / 180.0;
    }

    void setMagnitude(double magnitude)
    {
        this->magnitude = magnitude;
    }

    // Returns the angle in degrees
    double getAngle(double angle)
    {
        return this->angle * 180.0 / M_PI;
    }

    double getMagnitude(double magnitude)
    {
        return this->magnitude;
    }

    // Convert to Cartesian coordinates
    double getX() const
    {
        return magnitude * cos(angle); // Assuming angle is in radians
    }

    double getY() const
    {
        return magnitude * sin(angle); // Assuming angle is in radians
    }

    // Rotate the vector by a given angle in degrees
    void rotate(double angle)
    {
        this->angle += angle * M_PI / 180.0; // Convert angle to radians
    }
};

#endif // ANGLEDIRECTION_H