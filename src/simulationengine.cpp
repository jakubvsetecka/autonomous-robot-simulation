/**
 * @file simulationengine.cpp
 * @brief This file contains the implementation of the SimulationEngine class.
 * @details It is a subclass of the QGraphicsScene class and represents the simulation engine for the game.
 * @authors Tomáš Hobza, Jakub Všetečka
 * @date 02.05.2024
 */

#include "simulationengine.hpp"
#include "obstacle.hpp"
#include <QGraphicsSceneMouseEvent>
#include <qdir.h>

SimulationEngine::SimulationEngine(QObject *parent, int fps, qreal simulationSpeed)
    : QGraphicsScene(parent) {
    // Set the frame rate and simulation speed
    setFPS(fps);
    setSimulationSpeed(simulationSpeed);

    // Set the background color
    setBackgroundBrush(QBrush(Qt::white));
}

SimulationEngine::~SimulationEngine() {}

int SimulationEngine::getFPS() {
    return fps;
}

void SimulationEngine::setFPS(int fps) {
    this->fps = fps;
    updateTimeConstant();
}

int SimulationEngine::getFrameTime() {
    return 1000 / fps;
}

qreal SimulationEngine::getSimulationSpeed() {
    return simulationSpeed;
}

void SimulationEngine::setSimulationSpeed(qreal speed) {
    simulationSpeed = speed;
    updateTimeConstant();
}

qreal *SimulationEngine::getTimeConstant() {
    return &timeConstant;
}

void SimulationEngine::updateTimeConstant() {
    timeConstant = 1000 / getFPS() * simulationSpeed;
}

Robot *SimulationEngine::getControlledRobot() {
    return controlledRobot;
}

void SimulationEngine::setControlledRobot(Robot *robot) {
    controlledRobot = robot;
}

bool SimulationEngine::isInsideScene(const QPointF &point) const {
    QRectF sceneRect = this->sceneRect();
    return sceneRect.contains(point);
}

bool SimulationEngine::saveSimulation(const QString &filename) {
    // Create the "simulations" folder if it doesn't exist
    QDir simulationsDir("examples");
    if (!simulationsDir.exists()) {
        if (!simulationsDir.mkpath(".")) {
            qWarning("Failed to create simulations folder.");
            return false;
        }
    }

    QString mutableFilename = filename; // Create a mutable copy of the filename
    mutableFilename.replace("/", "\\");

    // Open or create the save file inside the "examples" folder
    QFile saveFile(simulationsDir.filePath(mutableFilename + ".json"));
    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    // Replace '/' with escape character

    // Write the JSON data to the file
    QJsonObject gameObject = toJson();
    saveFile.write(QJsonDocument(gameObject).toJson());

    return true;
}

QJsonObject SimulationEngine::toJson() const {
    QJsonObject json;
    json["fps"] = fps;
    json["simulationSpeed"] = simulationSpeed;

    QJsonObject objects;
    QJsonObject robots;
    QJsonArray obstacles;
    QJsonArray autoRobots;
    QJsonArray controlledRobots;

    for (QGraphicsItem *item : items()) {
        if (item->type() == Obstacle::Type) {
            Obstacle *obstacle = qgraphicsitem_cast<Obstacle *>(item);
            obstacles.append(obstacle->toJSON());
        } else if (item->type() == AutoRobot::Type) {
            AutoRobot *autoRobot = qgraphicsitem_cast<AutoRobot *>(item);
            autoRobots.append(autoRobot->toJSON());
        } else if (item->type() == Robot::Type) {
            Robot *robot = qgraphicsitem_cast<Robot *>(item);
            controlledRobots.append(robot->toJSON());
        }
    }

    robots["autoRobots"] = autoRobots;
    robots["controlledRobots"] = controlledRobots;

    objects["obstacles"] = obstacles;
    objects["robots"] = robots;

    json["objects"] = objects;

    return json;
}

void SimulationEngine::read(const QJsonObject &json) {
    if (const QJsonValue v = json["fps"]; v.isDouble())
        setFPS(v.toInt());

    if (const QJsonValue v = json["simulationSpeed"]; v.isDouble())
        setSimulationSpeed(v.toDouble());

    if (const QJsonValue v = json["objects"]; v.isObject()) {
        QJsonObject objects = v.toObject();

        if (const QJsonValue v = objects["obstacles"]; v.isArray()) {
            QJsonArray obstacles = v.toArray();
            for (const QJsonValue &obstacleValue : obstacles) {
                if (obstacleValue.isObject()) {
                    addItem(Obstacle::fromJSON(obstacleValue.toObject()));
                }
            }
        }
        if (const QJsonValue v = objects["robots"]; v.isObject()) {
            QJsonObject robots = v.toObject();

            if (const QJsonValue v = robots["autoRobots"]; v.isArray()) {
                QJsonArray autoRobots = v.toArray();
                for (const QJsonValue &autoRobotValue : autoRobots) {
                    if (autoRobotValue.isObject()) {
                        addItem(AutoRobot::fromJSON(autoRobotValue.toObject(), &timeConstant));
                    }
                }
            }
            if (const QJsonValue v = robots["controlledRobots"]; v.isArray()) {
                QJsonArray controlledRobots = v.toArray();
                for (const QJsonValue &controlledRobotValue : controlledRobots) {
                    if (controlledRobotValue.isObject()) {
                        addItem(Robot::fromJSON(controlledRobotValue.toObject(), &timeConstant));
                    }
                }
            }
        }
    }
}

bool SimulationEngine::loadSimulation(QString filename) {
    // Clear the scene
    clear();

    // Open the save file
    QFile loadFile("examples/" + filename + ".json");
    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    // Read the JSON data from the file
    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    read(loadDoc.object());

    return true;
}

void SimulationEngine::clearScene() {
    clear();
}
