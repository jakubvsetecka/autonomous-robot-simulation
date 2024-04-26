#include "simulation.h"
#include "./ui_mainwindow.h"
#include <QJsonArray> // Add missing include directive

Simulation::Simulation(QGraphicsScene *scene)
    : scene(scene) {
}

Simulation::~Simulation() {
    delete scene;
    qDeleteAll(objects);
    objects.clear();
}

void Simulation::addObject(GameObject *object) {
    objects.append(object);
    scene->addItem(object);
}

void Simulation::removeObject(GameObject *object) {
    objects.removeOne(object);
    scene->removeItem(object);
    delete object;
}

void Simulation::updateObjects() {
    for (GameObject *obj : objects) {
        obj->update();
    }
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
    for (const GameObject *obj : objects) {
        itemsArray.append(obj->toJson()); // Ensure GameObject has a toJson method
    }
    root["items"] = itemsArray;
    return root;
}

bool Simulation::deserialize(const QJsonObject &json) {
    QJsonArray itemsArray = json["items"].toArray();
    for (const QJsonValue &value : itemsArray) {
        QJsonObject objJson = value.toObject();
        GameObject *obj = GameObject::fromJson(objJson); // Static method to create objects from JSON
        addObject(obj);
    }
    return true;
}
