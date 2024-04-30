#include "simulationengine.hpp"
#include "obstacle.hpp"

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

#include <QGraphicsSceneMouseEvent>
#include <qdir.h>

void SimulationEngine::setControlledRobot(Robot *robot) {
    controlledRobot = robot;
    addItem(controlledRobot);
}

bool SimulationEngine::isInsideScene(const QPointF &point) const {
    QRectF sceneRect = this->sceneRect();
    return sceneRect.contains(point);
}

bool SimulationEngine::saveSimulation(const QString &filename) {
    // Create the "simulations" folder if it doesn't exist
    QDir simulationsDir("simulations");
    if (!simulationsDir.exists()) {
        if (!simulationsDir.mkpath(".")) {
            qWarning("Failed to create simulations folder.");
            return false;
        }
    }

    // Open or create the save file inside the "simulations" folder
    QFile saveFile(simulationsDir.filePath(filename + ".json"));
    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    // Write the JSON data to the file
    QJsonObject gameObject = toJson();
    saveFile.write(QJsonDocument(gameObject).toJson());

    return true;
}

QJsonObject SimulationEngine::toJson() const {
    QJsonObject json;
    json["fps"] = fps;
    json["simulationSpeed"] = simulationSpeed;

    // QJsonObject controlledRobotObject;
    // controlledRobotObject["x"] = controlledRobot->pos().x();
    // controlledRobotObject["y"] = controlledRobot->pos().y();
    // controlledRobotObject["rotation"] = controlledRobot->rotation();
    // controlledRobotObject["moveSpeed"] = controlledRobot->getMoveSpeed();
    // controlledRobotObject["rotationSpeed"] = controlledRobot->getRotationSpeed();
    // gameObject["controlledRobot"] = controlledRobotObject;

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

bool SimulationEngine::loadSimulation() {
    // Clear the scene
    clear();

    // Open the save file
    QFile loadFile("simulations/test13.json");
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