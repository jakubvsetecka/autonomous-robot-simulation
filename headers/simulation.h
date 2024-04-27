#ifndef SIMULATION_H
#define SIMULATION_H

#include "gameobject.h" // Include the definitions of your game objects
#include "obstacle.h"
#include "robot.h"
#include <QFile>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QJsonDocument>
#include <QJsonObject>
#include <QList>

class Simulation {
  public:
    Simulation();
    ~Simulation();

    void addObject(Robot *object);       // Add objects to the simulation
    void addObject(Obstacle *object);    // Add objects to the simulation
    void removeObject(Robot *object);    // Remove objects from the simulation
    void removeObject(Obstacle *object); // Remove objects from the simulation
    void updateObjects();                // Update all objects in the simulation
    bool save(const QString &filename);  // Save current state to a file
    bool load(const QString &filename);  // Load state from a file
    void checkCollisions();              // Check for collisions between objects

  private:
    std::list<Robot *> robots;       // List to hold all objects
    std::list<Obstacle *> obstacles; // List to hold all objects
    float frameTTL = 1/60;                // Speed of the simulation

    QJsonObject serialize() const;             // Serialize the scene to a JSON object
    bool deserialize(const QJsonObject &json); // Deserialize the scene from a JSON object
};

#endif // SIMULATION_H
