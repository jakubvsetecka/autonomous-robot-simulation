#include "simulation.h"
#include "./ui_mainwindow.h"
#include "controlledrobot.h" // Include the ControlledRobot class
#include "obstacle.h"
#include "obstacle.h" // Include the header file for the Obstacle class
#include "robot.h"    // Include the header file for the Robot class
#include <QJsonArray> // Add missing include directive
#include <QJsonValue> // Add missing include directive
#include <iostream>

Simulation::Simulation(QGraphicsScene *scene)
    : scene(scene)
{
}

Simulation::~Simulation()
{
    delete scene;
    qDeleteAll(robots);
    qDeleteAll(obstacles);
    robots.clear();
    obstacles.clear();
}

void Simulation::addObject(Robot *object)
{
    robots.append(object);
    scene->addItem(object);

    // Use dynamic_cast to check if the object is a ControlledRobot
    if (ControlledRobot *controlledRobot = dynamic_cast<ControlledRobot *>(object))
    {
        object->setFocus();
    }
}
void Simulation::addObject(Obstacle *object)
{
    obstacles.append(object);
    scene->addItem(object);
}

void Simulation::removeObject(Robot *object)
{
    robots.removeOne(object);
    scene->removeItem(object);
    delete object;
}

void Simulation::removeObject(Obstacle *object)
{
    obstacles.removeOne(object);
    scene->removeItem(object);
    delete object;
}

void Simulation::updateObjects()
{
    for (Robot *obj : robots)
    {
        // obj->update();
        // obj->enslaveToTime(frameTTL);
    }
    checkCollisions();
}

bool Simulation::save(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly))
    {
        return false;
    }
    QJsonObject simulationState = serialize();
    QJsonDocument doc(simulationState);
    file.write(doc.toJson());
    file.close();
    return true;
}

bool Simulation::load(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
    {
        return false;
    }
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    bool success = deserialize(doc.object());
    file.close();
    return success;
}

QJsonObject Simulation::serialize() const
{
    QJsonObject root;
    QJsonArray itemsArray;

    for (const GameObject *obj : obstacles)
    {
        itemsArray.append(obj->toJson()); // Ensure GameObject has a toJson method
    }

    for (const GameObject *obj : robots)
    {
        itemsArray.append(obj->toJson()); // Ensure GameObject has a toJson method
    }

    root["items"] = itemsArray;
    return root;
}

bool Simulation::deserialize(const QJsonObject &json)
{
    QJsonArray itemsArray = json["items"].toArray();
    for (const QJsonValue &value : itemsArray)
    {
        QJsonObject objJson = value.toObject();
        GameObject *obj = GameObject::fromJson(objJson); // Static method to create objects from JSON
        // addObject(obj);
    }
    return true;
}

void Simulation::checkCollisions()
{
    for (auto item : scene->items())
    {
        if (item->data(0) != "gridLine")
        {
            std::cout << "scena: " << scene->width() << " " << scene->height() << std::endl;
            std::cout << "item: " << item->x() << " " << item->y() << std::endl;

            if (item->x() < 0 || item->x() > scene->width() || item->y() < 0 || item->y() > scene->height())
            {
                std::cout << "kurva" << std::endl;
            }
            else
            {
                item->setPos(100, 100);
            }
        }
    }

    // for (Robot *robot : robots)
    // {
    //     std::cout << "scena: " << scene->width() << " " << scene->height() << std::endl;
    //     std::cout << "robot: " << robot->x() << " " << robot->y() << std::endl;
    //     if (robot->x() < 0 || robot->x() > scene->width() || robot->y() < 0 || robot->y() > scene->height())
    //     {
    //         std::cout << "kurva" << std::endl;
    //         robot->handleCollision();
    //         robot->angleDir.setMagnitude(0);
    //     }

    //     for (Obstacle *obstacle : obstacles)
    //     {

    //         if (robot->collidesWithItem(obstacle))
    //         {
    //             robot->handleCollision();
    //         }
    //     }
    // }
}