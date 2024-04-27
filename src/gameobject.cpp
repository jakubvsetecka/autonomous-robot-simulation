/**
 * @file gameobject.cpp
 * @brief This file provides the implementation of the GameObject class.
 * @authors Jakub Všetečka, Tomáš Hobza
 */

#include "gameobject.h"
#include <QBrush>
#include <QJsonValue>

GameObject::GameObject(pair<float, float> position, float dimension, double angle, double velocity)
    : position(position), angleDir(angle, velocity), dimension(dimension) {
}

GameObject::~GameObject() {}

void GameObject::update() {
    // Placeholder for update code
}

QJsonValue GameObject::toJson() const {
    // Convert object to JSON
    // Placeholder for JSON conversion code
}

GameObject *GameObject::fromJson(const QJsonObject &obj) {
    // Create object from JSON
    // Placeholder for JSON object creation code
}

bool GameObject::collidesWithItem(GameObject *item) {
    // Placeholder for collision detection code
    // TODO
    return false;
}

void GameObject::enslaveInTime(float frameTTL) {
    // TODO: Optimize the shit out of this
    position.first /= frameTTL;
    position.second /= frameTTL;
}