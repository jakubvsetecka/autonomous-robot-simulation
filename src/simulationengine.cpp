#include "simulationengine.hpp"
#include "obstacle.hpp"

qreal SimulationEngine::timeConstant = 0.5;

SimulationEngine::SimulationEngine(QObject *parent, int fps, int simulationSpeed)
    : QGraphicsScene(parent) {
    // Set the frame rate and simulation speed
    this->fps = fps;
    this->simulationSpeed = simulationSpeed;

    // Set the static time constant
    SimulationEngine::timeConstant = getFrameTime() * simulationSpeed;

    // Testing obsacle
    Obstacle *oznuk = new Obstacle();
    oznuk->setBrush(QBrush(Qt::blue));
    oznuk->setTransformOriginPoint(oznuk->rect().center());
    oznuk->setRotation(45);
    addItem(oznuk);

    // Create a robot and set it as the controlled robot
    Robot *robutek = new Robot();
    robutek->setPos(100, 100);
    setControlledRobot(robutek);

    // Add an autonomous robot
    AutoRobot *samorobutek = new AutoRobot(nullptr, 10, Robot::RotationDirection::Right, 7, 1);
    samorobutek->setPos(150, 150);
    addItem(samorobutek);
}

SimulationEngine::~SimulationEngine() {}

int SimulationEngine::getFPS() {
    return fps;
}

int SimulationEngine::getFrameTime() {
    return 1000 / fps;
}

qreal SimulationEngine::getSimulationSpeed() {
    return simulationSpeed;
}

Robot *SimulationEngine::getControlledRobot() {
    return controlledRobot;
}

void SimulationEngine::setControlledRobot(Robot *robot) {
    controlledRobot = robot;
    addItem(controlledRobot);
}

void SimulationEngine::addObstacle() {
    Obstacle *obstacle = new Obstacle();
    addItem(obstacle);
}

void SimulationEngine::addAutoRobot() {
    AutoRobot *autoRobot = new AutoRobot(nullptr, 10, Robot::RotationDirection::Right, 7, 1);
    addItem(autoRobot);
}

void SimulationEngine::addControlledRobot() {
    Robot *robot = new Robot();
    setControlledRobot(robot);
}