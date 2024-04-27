/**
 * @file angledirection.h
 * @brief This file provides the definition of the AngleDirection class.
 * @authors Jakub Všetečka, Tomáš Hobza
 */

#ifndef ANGLEDIRECTION_H
#define ANGLEDIRECTION_H

#include <cmath>

class AngleDirection {
  public:
    double angle;     // Angle in radians
    double magnitude; // Magnitude of the vector

    // Constructor
    AngleDirection(double angle = 0.0, double magnitude = 0.0)
        : angle(angle), magnitude(magnitude) {}

    // Set angle in degrees
    void setAngle(double angle) {
        this->angle = angle * M_PI / 180.0; // Convert to radians
    }

    // Convert to Cartesian coordinates
    double getX() const {
        return magnitude * cos(angle); // Assuming angle is in radians
    }

    double getY() const {
        return magnitude * sin(angle); // Assuming angle is in radians
    }

    // Rotate the angle by a given amount in degrees
    void rotate(double amount) {
        double in_radians = amount * M_PI / 180.0;
        angle += in_radians;
    }

    // Other methods as needed, such as updating angle or magnitude, etc.
};

#endif // ANGLEDIRECTION_H