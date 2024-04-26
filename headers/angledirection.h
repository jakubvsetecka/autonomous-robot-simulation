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
    double angle;     // Angle in degrees or radians
    double magnitude; // Magnitude of the vector

    // Constructor
    AngleDirection(double angle = 0.0, double magnitude = 0.0)
        : angle(angle), magnitude(magnitude) {}

    // Convert to Cartesian coordinates
    double getX() const {
        return magnitude * cos(angle); // Assuming angle is in radians
    }

    double getY() const {
        return magnitude * sin(angle); // Assuming angle is in radians
    }

    // Other methods as needed, such as updating angle or magnitude, etc.
};

#endif // ANGLEDIRECTION_H