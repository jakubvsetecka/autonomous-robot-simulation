#ifndef SIMULATION_H
#define SIMULATION_H

#include "gameobject.h" // Include the definitions of your game objects
#include <QFile>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QJsonDocument>
#include <QJsonObject>
#include <QList>

class Simulation {
  public:
    Simulation(QGraphicsScene *scene);
    ~Simulation();

    void addObject(GameObject *object);    // Add objects to the simulation
    void removeObject(GameObject *object); // Remove objects from the simulation
    void updateObjects();                  // Update all objects in the simulation
    bool save(const QString &filename);    // Save current state to a file
    bool load(const QString &filename);    // Load state from a file

  private:
    QGraphicsScene *scene;
    QList<GameObject *> objects; // List to hold all objects

    QJsonObject serialize() const;             // Serialize the scene to a JSON object
    bool deserialize(const QJsonObject &json); // Deserialize the scene from a JSON object
};

#endif // SIMULATION_H
