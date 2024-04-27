#include "simulation.h"
#include "./ui_mainwindow.h"
#include "controlledrobot.h" // Include the ControlledRobot class
#include "obstacle.h"
#include "obstacle.h" // Include the header file for the Obstacle class
#include "robot.h"    // Include the header file for the Robot class
#include <QJsonArray> // Add missing include directive
#include <QJsonValue> // Add missing include directive
#include <iostream>

Simulation::Simulation() {}

Simulation::~Simulation() {
    qDeleteAll(robots);
    qDeleteAll(obstacles);
    robots.clear();
    obstacles.clear();
}

void Simulation::addObject(Robot *object) {
    robots.push_back(object);

    // Use dynamic_cast to check if the object is a ControlledRobot
    if (ControlledRobot *controlledRobot = dynamic_cast<ControlledRobot *>(object)) {
        // object->setFocus();
    }
}
void Simulation::addObject(Obstacle *object) {
    obstacles.push_back(object);
}

void Simulation::removeObject(Robot *object) {
    robots.remove(object);
    delete object;
}

void Simulation::removeObject(Obstacle *object) {
    obstacles.remove(object);
    delete object;
}

void Simulation::updateObjects() {
    for (Robot *obj : robots) {
        obj->update();
        obj->enslaveInTime(frameTTL);
    }
    checkCollisions();
}

bool Simulation::save(const QString &filename) {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }
    QJsonObject simulationState = serialize();
    QJsonDocument doc(simulationState);
    file.write(doc.toJson());
    file.close();
    return true;
}

bool Simulation::load(const QString &filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    bool success = deserialize(doc.object());
    file.close();
    return success;
}

QJsonObject Simulation::serialize() const {
    QJsonObject root;
    QJsonArray itemsArray;

    for (const GameObject *obj : obstacles) {
        itemsArray.push_back(obj->toJson()); // Ensure GameObject has a toJson method
    }

    for (const GameObject *obj : robots) {
        itemsArray.push_back(obj->toJson()); // Ensure GameObject has a toJson method
    }

    root["items"] = itemsArray;
    return root;
}

bool Simulation::deserialize(const QJsonObject &json) {
    QJsonArray itemsArray = json["items"].toArray();
    for (const QJsonValue &value : itemsArray) {
        QJsonObject objJson = value.toObject();
        GameObject *obj = GameObject::fromJson(objJson); // Static method to create objects from JSON
        // addObject(obj);
    }
    return true;
}

void Simulation::checkCollisions() {
    for (Robot *robot : robots) {
        for (Obstacle *obstacle : obstacles) {
            if (robot->collidesWithItem(obstacle)) {
                robot->handleCollision();
            }
        }
    }
}