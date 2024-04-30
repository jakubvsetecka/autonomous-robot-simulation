#include "simulationengine.hpp"
#include "obstacle.hpp"

SimulationEngine::SimulationEngine(QObject *parent, int fps, qreal simulationSpeed)
    : QGraphicsScene(parent) {
    // Set the frame rate and simulation speed
    setFPS(fps);
    setSimulationSpeed(simulationSpeed);

    // Set the background color
    setBackgroundBrush(QBrush(Qt::white));

    // Create a robot and set it as the controlled robot
    Robot *robutek = new Robot(nullptr, &timeConstant);
    robutek->setPos(12.5, 12.5);
    setControlledRobot(robutek);

    Obstacle *obstacle = new Obstacle();
    obstacle->setPos(200, 200);
    addItem(obstacle);

    AutoRobot *samorobutek = new AutoRobot(nullptr, 0, Robot::RotationDirection::Right, 1, 1, &timeConstant);
    samorobutek->setPos(130, 100);
    addItem(samorobutek);

    AutoRobot *druhy_samorobutek = new AutoRobot(nullptr, 0, Robot::RotationDirection::Right, 1, 1, &timeConstant);
    druhy_samorobutek->setPos(100, 100);
    addItem(druhy_samorobutek);

    // // Add an autonomous robot
    // for (int i = 0; i < 3; i++)
    // {
    //     for (int j = 0; j < 3; j++)
    //     {
    //         AutoRobot *samorobutek = new AutoRobot(nullptr, 20, Robot::RotationDirection::Right, 1, 5, &timeConstant);
    //         samorobutek->setPos(150 + i * 20, 150 + j * 20);
    //         addItem(samorobutek);
    //     }
    // }
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

void SimulationEngine::updateTimeConstant() {
    timeConstant = 1000 / getFPS() * simulationSpeed;
}

Robot *SimulationEngine::getControlledRobot() {
    return controlledRobot;
}

void SimulationEngine::setControlledRobot(Robot *robot) {
    controlledRobot = robot;
    addItem(controlledRobot);
}

bool SimulationEngine::isInsideScene(const QPointF &point) const {
    QRectF sceneRect = this->sceneRect();
    return sceneRect.contains(point);
}